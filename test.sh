#!/usr/bin/bash

# ------------------------------
# User defined variables
# ------------------------------
readonly CURRENT_DIR=$(pwd)
readonly MINISHELL_DIR="${CURRENT_DIR}"
readonly MINISHELL_PATH="${MINISHELL_DIR}/minishell"
readonly TEST_DIR="${MINISHELL_DIR}/test"
readonly OUTPUT_DIR="${MINISHELL_DIR}/output"
readonly LOG_FILENAME="${MINISHELL_DIR}/result.log"
# ------------------------------

readonly EXPECT_STDOUT_FILE="${OUTPUT_DIR}/expect_stdout"
readonly EXPECT_STDERR_FILE="${OUTPUT_DIR}/expect_stderr"
readonly ACTUAL_STDOUT_FILE="${OUTPUT_DIR}/actual_stdout"
readonly ACTUAL_STDERR_FILE="${OUTPUT_DIR}/actual_stderr"

readonly EXPECT_FILES_DIR="${OUTPUT_DIR}/expect"
readonly ACTUAL_FILES_DIR="${OUTPUT_DIR}/actual"
readonly FILE_COMPARE_FILENAME="${OUTPUT_DIR}/file_compare.log"

readonly RED='\033[0;31m'
readonly GREEN='\033[0;32m'
readonly RESET='\033[0m'

readonly OK="[${GREEN}OK${RESET}]"
readonly NG="[${RED}NG${RESET}]"

result_all=0
result_ok=0
result_ng=0

build_minishell() {
        make -C ${MINISHELL_PATH}
}

start_test() {
        build_minishell
        rm -f ${LOG_FILENAME}
        if [ $? -ne 0 ]; then
                echo "Failed to build minishell"
                exit 1
        fi
}

clean_up() {
        rm -rf ${TEST_DIR}
        rm -rf ${OUTPUT_DIR}
        rm -f ${EXPECT_STDOUT_FILE} ${EXPECT_STDERR_FILE} ${ACTUAL_STDOUT_FILE} ${ACTUAL_STDERR_FILE} ${FILE_COMPARE_FILENAME}
}

set_up() {
        rm -rf ${TEST_DIR}
        rm -rf ${OUTPUT_DIR}
        rm -f ${EXPECT_STDOUT_FILE} ${EXPECT_STDERR_FILE} ${ACTUAL_STDOUT_FILE} ${ACTUAL_STDERR_FILE} ${FILE_COMPARE_FILENAME}
        mkdir -p ${TEST_DIR}
        mkdir -p ${OUTPUT_DIR}
        touch ${EXPECT_STDOUT_FILE} ${EXPECT_STDERR_FILE} ${ACTUAL_STDOUT_FILE} ${ACTUAL_STDERR_FILE} ${FILE_COMPARE_FILENAME}
}

print_category() {
        printf "%s\n" "[$1]"
}

exec_shell() {
        exec_bash "$test_cmd"
        exec_minishell "$test_cmd"
        replace_stderr
}

exec_bash() {
        rm -rf ${TEST_DIR}
        mkdir -p ${TEST_DIR}
        cd ${TEST_DIR}
        if [ ! -z "${prepare_cmd}" ]; then
                bash -c "${prepare_cmd}"
        fi
        printf "$1" | bash >${EXPECT_STDOUT_FILE} 2>${EXPECT_STDERR_FILE}
        expect_status=$?
        mkdir -p ${EXPECT_FILES_DIR}
        if [ "$(ls -A)" ]; then
                chmod 755 *
                cp -r * ${EXPECT_FILES_DIR}
        fi
        cd ${CURRENT_DIR}
}

exec_minishell() {
        rm -rf ${TEST_DIR}
        mkdir -p ${TEST_DIR}
        cd ${TEST_DIR}
        if [ ! -z "${prepare_cmd}" ]; then
                bash -c "${prepare_cmd}"
        fi
        printf "$1\nexit\n" | ${MINISHELL_PATH} >${ACTUAL_STDOUT_FILE} 2>${ACTUAL_STDERR_FILE}
        actual_status=$?
        mkdir -p ${ACTUAL_FILES_DIR}
        if [ "$(ls -A)" ]; then
                chmod 755 *
                cp -r * ${ACTUAL_FILES_DIR}
        fi
        cd ${CURRENT_DIR}
}

replace_stderr() {
        sed -i 's/bash: line [0-9]*:/bash:/g' ${EXPECT_STDERR_FILE}
        sed -i 's/bash:/minishell:/' ${EXPECT_STDERR_FILE}
        sed -i '/^minishell\$/d' ${ACTUAL_STDERR_FILE}
        sed -i '/^> /d' ${ACTUAL_STDERR_FILE}
        sed -i '/^exit$/d' ${ACTUAL_STDERR_FILE}
}

check_files_match() {
        local expect_dir="${OUTPUT_DIR}/expect"
        local actual_dir="${OUTPUT_DIR}/actual"

        # ファイル名のリストを取得
        local expect_files=$(find "${expect_dir}" -type f | sed "s|${expect_dir}/||")
        local actual_files=$(find "${actual_dir}" -type f | sed "s|${actual_dir}/||")

        # ファイル名が一致するかチェック
        if [ "${expect_files}" != "${actual_files}" ]; then
                echo "Number of files is different" >>${FILE_COMPARE_FILENAME}
                echo "Expect: ${expect_files}" >>${FILE_COMPARE_FILENAME}
                echo "Actual: ${actual_files}" >>${FILE_COMPARE_FILENAME}
        fi

        # ファイルの中身が一致するかチェック
        for file in ${expect_files}; do
                if ! diff "${expect_dir}/${file}" "${actual_dir}/${file}" >/dev/null; then
                        echo "File content is different" >>${FILE_COMPARE_FILENAME}
                        echo "File: ${file}" >>${FILE_COMPARE_FILENAME}
                        echo "Expect:" >>${FILE_COMPARE_FILENAME}
                        cat "${expect_dir}/${file}" >>${FILE_COMPARE_FILENAME}
                        echo "Actual:" >>${FILE_COMPARE_FILENAME}
                        cat "${actual_dir}/${file}" >>${FILE_COMPARE_FILENAME}
                fi
        done
}

is_ok() {
        if [ -z "${diff_stdout}" ] && [ -z "${diff_stderr}" ] && [ ${expect_status} -eq ${actual_status} ] && [ ! -s ${FILE_COMPARE_FILENAME} ]; then
                return 0
        else
                return 1
        fi
}

output_log() {
        if ! is_ok; then
                echo "====================================" >>${LOG_FILENAME}
                echo "[${result_all}]: ${assert_cmd}" >>${LOG_FILENAME}
                echo "Result: NG" >>${LOG_FILENAME}
                echo "------------------------------------" >>${LOG_FILENAME}
                echo "Expect status: ${expect_status}" >>${LOG_FILENAME}
                echo "Actual status: ${actual_status}" >>${LOG_FILENAME}
                echo "------------------------------------" >>${LOG_FILENAME}
                #echo "stdout diff:" >>${LOG_FILENAME}
                #echo "${diff_stdout}" >>${LOG_FILENAME}
                #echo "------------------------------------" >>${LOG_FILENAME}
                #echo "stderr diff:" >>${LOG_FILENAME}
                #echo "${diff_stderr}" >>${LOG_FILENAME}
                #echo "------------------------------------" >>${LOG_FILENAME}
                echo "Expect stdout:" >>${LOG_FILENAME}
                cat ${EXPECT_STDOUT_FILE} >>${LOG_FILENAME}
                echo "------------------------------------" >>${LOG_FILENAME}
                echo "Actual stdout:" >>${LOG_FILENAME}
                cat ${ACTUAL_STDOUT_FILE} >>${LOG_FILENAME}
                echo "------------------------------------" >>${LOG_FILENAME}
                echo "Expect stderr:" >>${LOG_FILENAME}
                cat ${EXPECT_STDERR_FILE} >>${LOG_FILENAME}
                echo "------------------------------------" >>${LOG_FILENAME}
                echo "Actual stderr:" >>${LOG_FILENAME}
                cat ${ACTUAL_STDERR_FILE} >>${LOG_FILENAME}
                echo "------------------------------------" >>${LOG_FILENAME}
                echo "File compare:" >>${LOG_FILENAME}
                cat ${FILE_COMPARE_FILENAME} >>${LOG_FILENAME}
                echo "====================================" >>${LOG_FILENAME}
                echo >>${LOG_FILENAME}
        fi
}

assert() {
        set_up
        result_all=$((result_all + 1))
        assert_cmd=$(echo $1 | cut -c 1-50)
        test_cmd=$(echo $1 | sed 's/;/\n/g')
        prepare_cmd=$2
        exec_shell
        diff_stdout=$(diff ${EXPECT_STDOUT_FILE} ${ACTUAL_STDOUT_FILE})
        diff_stderr=$(diff ${EXPECT_STDERR_FILE} ${ACTUAL_STDERR_FILE})
        check_files_match
        printf "%3d. %-50s " ${result_all} "${assert_cmd}"
        if is_ok; then
                result_ok=$((result_ok + 1))
                printf "${OK}\n"
        else
                result_ng=$((result_ng + 1))
                printf "${NG}"
                printf "("
                if [ ! -z "${diff_stdout}" ]; then
                        printf " stdout: ${NG}"
                fi
                if [ ! -z "${diff_stderr}" ]; then
                        printf " stderr: ${NG}"
                fi
                if [ ${expect_status} -ne ${actual_status} ]; then
                        printf " status: ${NG}"
                fi
                if [ -s ${FILE_COMPARE_FILENAME} ]; then
                        printf " file: ${NG}"
                fi
                printf " )\n"
        fi
        output_log
        clean_up
}

show_result() {
        echo ""
        echo "Result: ${result_ok} tests passed, ${result_ng} tests failed"
        echo "More detail: ${LOG_FILENAME}"
}

start_test

# Test
print_category "simple command"

assert "/usr/bin/true"
assert "/usr/bin/false"
assert "true"
assert "false"
assert "/bin/ls" "touch a b c .a .b .c"
assert "/bin/ls -a" "touch a b c .a .b .c"
assert "ls" "touch a b c .a .b .c"
assert "ls -a" "touch a b c .a .b .c"
assert "./ls" "touch a b c; cp /bin/ls ./ls"
assert "./ls -a" "touch a b c; cp /bin/ls ./ls"
assert "       "
assert "        "

print_category "not exist command"

assert "not_exist_command"
assert "not_exist_command | not_exist_command"
assert "./not_exist_command"
assert "./not_exist_command | ./not_exist_command"
assert "/not/exist/command"
assert "/not/exist/command | /not/exist/command"
assert "ls | not_exist_command" "touch a b c"
assert "ls | not_exist_command | ls" "touch a b c"
assert "ls | ./not_exist_command" "touch a b c"
assert "ls | ./not_exist_command | ls" "touch a b c"

print_category "permission denied"

#assert "./perm" "touch perm; chmod 000 perm"
#assert "./perm" "touch perm; chmod 100 perm"
#assert "./perm" "touch perm; chmod 300 perm"
#assert "./perm" "touch perm; chmod 500 perm"
assert "./ls" "touch a b c; cp /bin/ls ./ls; chmod 000 ls"
assert "./ls" "touch a b c; cp /bin/ls ./ls; chmod 100 ls"
assert "./ls" "touch a b c; cp /bin/ls ./ls; chmod 300 ls"
assert "./ls" "touch a b c; cp /bin/ls ./ls; chmod 500 ls"

print_category "directory"

assert "dir" "mkdir dir"
assert "./dir" "mkdir dir"

print_category "pipe"

assert "/bin/ls | /usr/bin/grep a" "touch aa ab ac"
assert "/bin/ls | /usr/bin/grep a | /usr/bin/grep b" "touch aa ab ac"
assert "ls | grep a" "touch aa ab ac"
assert "ls | grep a | grep b" "touch aa ab ac"

print_category "pipe (builtin command)"

assert "echo 'helloworld' | wc"
assert "echo 'helloworld' | echo 'helloworld' | wc"

print_category "redirection"

assert "> file"
assert "< file" "echo 42 > file"
assert ">> file"
assert ">> file" "echo 42 > file"
assert "<< EOF;hello;EOF"
assert "/usr/bin/echo 42 > file"
assert "/usr/bin/echo 42 > file; /usr/bin/echo 24 > file;"
assert "/usr/bin/echo 42 > no_perm" "touch no_perm; chmod 000 no_perm"
assert "/usr/bin/echo 42 >> file"
assert "/usr/bin/echo 42 >> no_perm" "touch no_perm; chmod 000 no_perm"
assert "/usr/bin/echo 42 > file; /usr/bin/echo 24 >> file"
assert "/usr/bin/echo 42 > file; /usr/bin/echo 24 >> file; /usr/bin/echo 42 > file"
assert "/usr/bin/echo hello > out1 > out2 > out3;"
assert "/usr/bin/echo hello >> out1 >> out2 >> out3;" "echo hello > out1; echo hello > out2; echo hello > out3;"
assert "/usr/bin/echo hello > out1 >> out2 > out3;" "echo hello > out1; echo hello > out2; echo hello > out3;"
assert "/usr/bin/echo hello > out1 > out2 >> out3;" "echo hello > out1; echo hello > out2; echo hello > out3;"
assert "/usr/bin/echo hello > out1 > no_perm > out2;" "echo hello > out1; echo hello > out2; touch no_perm; chmod 000 no_perm"
assert "/usr/bin/echo hello > out1 > out2 > no_perm;" "echo hello > out1; echo hello > out2; touch no_perm; chmod 000 no_perm"
assert "cat < file" "echo 42 > file"
assert "cat < file | cat" "echo 42 > file"
assert "cat < no_such_file"
assert "cat < no_such_file | cat"
assert "cat < no_perm" "touch no_perm; chmod 000 no_perm"
assert "cat < no_perm | cat" "touch no_perm; chmod 000 no_perm"
assert "cat < infile > outfile" "echo hello > infile"
assert "cat < infile >> outfile" "echo hello > infile; echo hello > outfile"
assert "cat < no_such_file > outfile"
assert "cat > outfile < no_such_file"
assert "cat < no_perm > outfile" "touch no_perm; chmod 000 no_perm"
assert "cat > outfile < no_perm" "touch no_perm; chmod 000 no_perm"
assert "cat file > outfile > outfile" "echo hello > file"
assert "export FILE=outfile; cat file > \$FILE" "echo hello > file"
assert "export FILE='a b'; cat file > \$FILE" "echo hello > file"
assert "cat file > \$NO_SUCH_VAR" "echo hello > file"
assert "cat file > \"\$NO_SUCH_VAR\"" "echo hello > file"

print_category "heredoc"

assert "cat << EOF;hello;EOF"
assert "cat << EOF;hello;   EOF;EOF"
assert "cat << 'EOF';hello;EOF"
assert "cat << 'E''O''F';hello;EOF"
assert "cat << EOF;\$HOME;EOF"
assert "cat << 'EOF';\$HOME;EOF"
assert "cat << 'E''O''F';\$HOME;EOF"
assert "cat << EOF;'\$HOME';EOF"
assert "cat << 'EOF';'\$HOME';EOF"
assert "cat << EOF;$?;EOF"
# manual
# assert cat << '' case

print_category "redirection (builtin command)"

assert "echo 42 > file"
assert "echo 42 > file; echo 42 > file;"
assert "echo 42 > no_perm" "touch no_perm; chmod 000 no_perm"
assert "echo 42 >> file"
assert "echo 42 >> no_perm" "touch no_perm; chmod 000 no_perm"
assert "echo 42 >> file; echo 42 >> file"
assert "echo hello > out1 > out2 > out3"
assert "echo hello >> out1 >> out2 >> out3" "echo hello > out1; echo hello > out2; echo hello > out3;"
assert "echo hello > out1 > no_perm > out2" "touch no_perm; chmod 000 no_perm"
assert "echo hello > out1 > out2 > no_perm" "touch no_perm; chmod 000 no_perm"
assert "echo < infile" "echo hello > infile"
assert "echo < infile < infile2" "echo hello > infile; echo hello > infile2"
assert "echo < no_such_file"
assert "echo < no_such_file | cat"
assert "echo < infile1 < no_perm < infile2" "touch no_perm; chmod 000 no_perm"
assert "echo < infile1 < infile2 < no_perm" "touch no_perm; chmod 000 no_perm"
assert "echo hello < infile > outfile" "echo 42tokyo > infile"

print_category "pipe and redirection"

assert "cat < infile | wc -l" "echo hello > infile"
assert "cat < infile | wc -l > outfile" "echo hello > infile; echo hello > infile"
assert "cat < infile > outfile | wc -l" "echo hello > infile; echo hello > infile"

print_category "pipe and redirection (invalid command & file)"

assert "cat < infile | wc -l > outfile"
assert "cat < infile > outfile | wc -l"
assert "cat < infile | wc -l > outfile" "touch infile; chmod 000 infile"
assert "cat < infile > outfile | wc -l" "touch infile; chmod 000 infile"
assert "cat < infile | wc -l > outfile" "touch outfile; chmod 000 outfile"
assert "cat < infile > outfile | wc -l" "touch outfile; chmod 000 outfile"

print_category "cd"

assert "cd dir; pwd; echo \$PWD" "mkdir dir"
assert "cd dir; cd .; pwd; echo \$PWD" "mkdir dir"
assert "cd dir; cd ./; pwd; echo \$PWD" "mkdir dir"
assert "cd dir; cd ..; pwd; echo \$PWD" "mkdir dir"
assert "cd dir; cd ../; pwd; echo \$PWD" "mkdir dir"
assert "cd dir; cd ../dir; pwd; echo \$PWD" "mkdir dir"
assert "cd /; pwd; echo \$PWD"
assert "cd /tmp; pwd; echo \$PWD"
assert "cd no_such_dir; pwd; echo \$PWD"
assert "cd hello world; pwd; echo \$PWD"
assert "cd /no/such/dir; pwd; echo \$PWD"
# assert "cd dir; cd ../no_such_dir/../dir; pwd; echo \$PWD" "mkdir dir" <- あきらめ
assert "cd hello world; pwd; echo \$PWD" "mkdir hello"
assert "cd dir; pwd; echo \$PWD" "mkdir dir; chmod 000 dir"
assert "cd link; pwd; echo \$PWD; cd ..; rm -rf link dir" "mkdir dir; ln -s dir link"
assert "cd link; pwd; echo \$PWD; rm -rf link" "mkdir dir; ln -s dir link; rmdir dir"
assert "cd dir; rmdir ../dir; cd ./; pwd; echo \$PWD; cd .; pwd; echo \$PWD; cd ./././; pwd; echo \$PWD; cd ../; pwd; echo \$PWD" "mkdir dir"
assert "cd a/b/c; rm -rf ../../b; cd ./; pwd; echo \$PWD; cd ../; pwd; echo \$PWD; cd ../; pwd; echo \$PWD" "mkdir -p a/b/c"
assert "cd; pwd; echo \$PWD"
assert "unset HOME; cd; pwd; echo \$PWD"
assert "export HOME=; cd; pwd; echo \$PWD"
assert "export HOME=./; cd; pwd; echo \$PWD"
assert "export HOME=''; cd; pwd; echo \$PWD"
assert "export HOME=a; cd; pwd; echo \$PWD" "mkdir -p a/b"
assert "export HOME=a/b; cd; pwd; echo \$PWD" "mkdir -p a/b"
assert "export HOME=./no_such_dir; cd; pwd; echo \$PWD"
assert "cd dir; cd -; pwd; echo \$PWD" "mkdir dir"
assert "cd dir; cd -; cd -; pwd; echo \$PWD" "mkdir dir"
assert "cd dir; cd -; cd -; cd -; pwd; echo \$PWD" "mkdir dir"
assert "cd a; cd b; cd c; cd -; pwd; echo \$PWD" "mkdir -p a/b/c"
assert "cd a; cd b; cd c; cd -; cd -; pwd; echo \$PWD" "mkdir -p a/b/c"
assert "unset OLDPWD; cd -; pwd; echo \$PWD"
assert "unset OLDPWD; cd -; cd -; pwd; echo \$PWD"
assert "unset OLDPWD; cd dir; cd -; pwd; echo \$PWD" "mkdir dir"
assert "unset OLDPWD; cd dir; cd -; cd -; pwd; echo \$PWD" "mkdir dir"
assert "unset PWD; unset OLDPWD; cd; pwd; echo \$PWD"
assert "unset PWD; unset OLDPWD; cd; cd -; pwd; echo \$PWD"
assert "unset PWD; unset OLDPWD; cd -; pwd; echo \$PWD"
# assert "cd //; pwd; echo \$PWD" <- あきらめ
assert "cd ///; pwd; echo \$PWD"
assert "cd //no/such/dir; pwd; echo \$PWD"
assert "cd ///no/such/dir; pwd; echo \$PWD"
# assert "export HOME=//; cd; pwd; echo \$PWD"
assert "export HOME=///; cd; pwd; echo \$PWD"
assert "unset PWD; cd; pwd; echo \$PWD"
assert "export PWD=; cd; pwd; echo \$PWD"
assert "export PWD=./; cd; pwd; echo \$PWD"
assert "export PWD=''; cd; pwd; echo \$PWD"
assert "export PWD=a; cd; pwd; echo \$PWD" "mkdir -p a/b"
assert "export PWD=a/b; cd; pwd; echo \$PWD" "mkdir -p a/b"
assert "export PWD=./no_such_dir; cd; pwd; echo \$PWD"
assert "cd ....; pwd; echo \$PWD"
assert "cd ............; pwd; echo \$PWD"

print_category "echo"

assert "echo"
assert "echo hello"
assert "echo       space    "
assert "echo '     space    '"
assert "echo hello world"
assert "echo 'hello world'"
assert "echo -n"
assert "echo -n hello"
assert "echo -n hello world"
assert "echo -nnnnnnnnnn"
assert "echo -nnnnnnnnnn hello"
assert "echo -nnnnnnnnnn hello world"
assert "echo -nnnnnnnnnn -nnnnnnnnnn"
assert "echo -nnnnnnnnnn -nnnnnnnnnn hello"
assert "echo -nnnnnnnnnn -nnnnnnnnnn hello world"
assert "echo -na"
assert "echo -na hello"
assert "echo -na hello world"
assert "echo -nnnnnannnnn"
assert "echo -nnnnnannnnn hello"
assert "echo -nana"
assert "echo hello -n"
assert "echo hello -nnnnnnnnnn"
assert "echo hello -n"
assert "echo hello -n world"
assert "echo '-n' hello"
# unsupport backslash
#assert "echo \"-n\" hello"
#assert "echo '-n' 'hello'"
#assert "echo \"-n\" \"hello\""
#assert "echo \-\n h\e\l\l\o"
#assert "echo '\-\n' 'h\e\l\l\o'"
#assert "echo \"\-\n\" \"h\e\l\l\o\""
assert 'echo $HOME'
assert 'echo "$HOME"'
assert "echo '\$HOME'"
assert 'echo $HOME$NOTHING$HOME'
assert "echo a '' b '' c"
assert "echo $ $ $"

print_category "env"

assert "env | grep -v -E '^_' | sort"
assert "env | grep -v -E '^_' | sort" "export HOGE=42"
assert "cd dir; env | grep -v -E '^_' | sort" "mkdir dir"
assert "export A B C D; env | grep -v -E '^_' | sort"

print_category "exit"

assert "exit"
assert "exit 0"
assert "exit 1"
assert "exit -1"
assert "exit 42"
assert "exit +42"
assert "exit -42"
assert "exit 255"
assert "exit 256"
assert "exit 2147483647"
assert "exit 2147483648"
assert "exit -2147483648"
assert "exit -2147483649"
assert "exit 9223372036854775807"
assert "exit 9223372036854775808"
assert "exit -9223372036854775808"
assert "exit -9223372036854775809"
assert "exit '        42       '"
assert "exit --42"
assert "exit ++42"
assert "exit -+42"
assert "exit a"
assert "exit helloworld"
assert "exit 42a"
assert "exit +"
assert "exit -"
assert "exit '              '"
assert "exit '  '"
assert "exit 42 42"
assert "exit a b"
assert "exit 42 a"
assert "exit a 42 b"
assert "exit | exit"
assert "exit 42 | exit"
assert "exit 42 | exit 24"
assert "echo hello | exit"
assert "echo hello | exit 42"
assert "echo hello | exit 42 | echo world"
assert "echo hello | exit 42 | echo world | exit 24"

print_category "export"

assert "export | grep -v -E '^declare -x _'"
assert "export | grep -v -E '^declare -x _'" "export HOGE=42"
assert "export =; export | grep -v -E '^declare -x _'"
assert "export TEST=42; env | grep -v -E '^_' | sort"
assert "export TEST=42; env | grep -v -E '^_' | sort; export TEST=24; env | grep -v -E '^_' | sort"
assert "export TEST; env | grep -v -E '^_' | sort"
assert "export TEST='' ; env | grep -v -E '^_' | sort"
assert "export TEST=; env | grep -v -E '^_' | sort"
assert "export TEST=A=B=C; env | grep -v -E '^_' | sort"
assert "export TEST1=42 TEST2=24; env | grep -v -E '^_' | sort"
assert "export TEST1=42 IVNALID+-NAME=24 TEST2=42; env | grep -v -E '^_' | sort"
assert "export =EMPTY; env | grep -v -E '^_' | sort"
assert "export 1 _+ _OK _2? _OK2=VAR =NG OK3=; env | grep -v -E '^_' | sort"
assert "export dquote='\"' dollar='$' backslash='\' backquote='\`'; env | grep -v -E '^_' | sort"

print_category "pwd"

assert "echo \$PWD"
assert "echo \$OLDPWD"
assert "export PWD=/; echo \$PWD"
assert "export OLDPWD=/; echo \$OKDPWD"
assert "pwd"
assert "export PWD=/; pwd"
assert "pwd; echo \$PWD; echo \$OLDPWD" "mkdir dir; cd dir"
assert "pwd; rmdir dir; rm -f link" "mkdir dir; ln -s dir link; cd link"
assert "export PWD=; export OLDPWD=; pwd; echo \$PWD; echo \$OLDPWD"
assert "cd; pwd; echo \$PWD; echo \$OLDPWD"
assert "cd dir; pwd; echo \$PWD; echo \$OLDPWD" "mkdir dir"
assert "cd /tmp; pwd; echo \$PWD; echo \$OLDPWD"
assert "cd no_such_dir; pwd; echo \$PWD; echo \$OLDPWD"
assert "cd .; pwd; echo \$PWD; echo \$OLDPWD"
assert "cd ..; pwd; echo \$PWD; echo \$OLDPWD"
assert "cd /; pwd; echo \$PWD; echo \$OLDPWD"
assert "cd ////; pwd; echo \$PWD; echo \$OLDPWD"
assert "cd /tmp///; pwd; echo \$PWD; echo \$OLDPWD"
assert "cd dir; rmdir ../dir; pwd; echo \$PWD; echo \$OLDPWD" "mkdir dir"
assert "cd dir; rmdir ../dir; cd ../; pwd; echo \$PWD; echo \$OLDPWD" "mkdir dir"

print_category "unset"

assert "unset; env | grep -v -E '^_' | sort"
assert "export A=42; unset A; env | grep -v -E '^_' | sort"
assert "export _A=42; unset _A; env | grep -v -E '^_' | sort"
assert "export A=42 B=24 C=42; unset A B C; env | grep -v -E '^_' | sort"
assert "export A=42 B=24 C=42; unset A =invalid= B; env | grep -v -E '^_' | sort"
assert "unset NO_SUCH_VAR; env | grep -v -E '^_' | sort"
assert "unset 1 | env | grep -v -E '^_' | sort"
assert "unset _+ _OK _2? _OK2=VAR =NG OK3=; env | grep -v -E '^_' | sort"
assert "unset A=a B=b C=c; env | grep -v -E '^_' | sort"

print_category "path"

assert "echo \$PATH"
assert "export PATH=':'; ls" "touch a b c; cp /bin/ls ./ls"
assert "export PATH=':/'; ls" "touch a b c; cp /bin/ls ./ls"
assert "export PATH='::'; ls" "touch a b c; cp /bin/ls ./ls"
assert "export PATH='/:'; ls" "touch a b c; cp /bin/ls ./ls"
assert "export PATH='/bin:'; ls" "touch a b c; cp /bin/ls ./ls"
assert "export PATH=':/bin'; ls" "touch a b c; cp /bin/ls ./ls"
assert "export PATH='::/bin:::'; ls" "touch a b c; cp /bin/ls ./ls"
assert "export PATH='hello:'; ls" "touch a b c; cp /bin/ls ./ls"
assert "export PATH=''; ls"
assert "export PATH=''; ls" "touch a b c; cp /bin/ls ./ls"
assert "unset PATH; ls"
assert "unset PATH; ls" "touch a b c; cp /bin/ls ./ls"

print_category "shlvl"

assert "echo \$SHLVL"
assert "echo \$SHLVL" "export SHLVL=0"
assert "echo \$SHLVL" "export SHLVL=999"
assert "echo \$SHLVL" "export SHLVL=1000"
assert "echo \$SHLVL" "export SHLVL=+42"
assert "echo \$SHLVL" "export SHLVL=-1"
assert "echo \$SHLVL" "export SHLVL=4294967295"
assert "echo \$SHLVL" "export SHLVL=4294967296"
assert "echo \$SHLVL" "export SHLVL=-4294967296"
assert "echo \$SHLVL" "export SHLVL=-4294967297"
assert "echo \$SHLVL" "export SHLVL=hello"
assert "echo \$SHLVL" "export SHLVL='42 42'"
assert "echo \$SHLVL" "export SHLVL=42a"

print_category "last command"

assert "export _=42; echo \$_;"

print_category "exit status"

assert "echo \$?"
assert "echo \$?0"
assert "echo \$?1"
assert "true; echo \$?"
assert "false; echo \$?"
assert "echo | exit 255; echo \$?"
assert "echo | exit 256; echo \$?"
assert "echo | exit 2147483647; echo \$?"
assert "echo | exit 2147483648; echo \$?"
assert "echo | exit -2147483648; echo \$?"
assert "echo | exit -2147483649; echo \$?"
assert "echo | exit 9223372036854775807; echo \$?"
assert "echo | exit 9223372036854775808; echo \$?"
assert "echo | exit -9223372036854775808; echo \$?"
assert "echo | exit -9223372036854775809; echo \$?"

print_category "quote"

assert "echo 'hello'"
assert "echo 'hello world'"
assert "echo 'hello' 'world'"
assert "echo 'hello' world"
assert "echo hello 'world'"
assert "echo '\"hello\"'"
assert "echo \"'hello'\""

print_category "expand tilde"

assert "echo ~"
assert "echo ~/"
assert "echo ~/path/to/dir"
assert "echo '~'"
assert "echo '~/'"
assert "echo '~/path/to/dir'"
assert "echo \"~\""
assert "echo \"~/\""
assert "echo \"~/path/to/dir\""

print_category "expand environment variable"

assert "export HOGE=42; echo \$HOGE"
assert "export HOGE=42; echo \"\$HOGE\""
assert "export HOGE=42; echo \'\$HOGE\'"
assert "export HOGE=42; echo \$HOGE\$HOGE"
assert "export HOGE=42; echo hoge\$HOGE"
assert "export HOGE=42; echo \$HOGEhoge"
assert "export HOGE=42; echo hoge\$HOGEhoge"
assert "export HOGE=42; echo \$HOGE'HOGE'"
assert "export HOGE=42; echo \$HOGE\"HOGE\""
assert "export HOGE=42; echo hoge\"\$HOGE\""
assert "export HOGE=42; echo \$+HOGE"

print_category "word split"

assert "export CMD='echo hello'; \$CMD"
assert "export CMD='echo hello'; \$CMD world"
assert "export FILES='a b c'; cat \$FILES" "echo hello > a; echo world > b; echo helloworld > c"

print_category "quote empty string"

assert "wc ''"
assert "wc \"\""
assert "export DIR=dir; cd \$EMPTY \$DIR; pwd; echo \$PWD" "mkdir dir"
assert "export DIR=dir; cd \"\$EMPTY\" \$DIR; pwd; echo \$PWD" "mkdir dir"
assert "export DIR=dir; cd \'\$EMPTY\' \$DIR; pwd; echo \$PWD" "mkdir dir"

show_result
