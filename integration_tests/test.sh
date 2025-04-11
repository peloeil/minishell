#!/usr/bin/env bash

# Define color codes for output formatting
readonly ESC=$(printf '\033')
readonly END="${ESC}[0m"
readonly RED="${ESC}[31m"
readonly GREEN="${ESC}[32m"

print_ok() {
    printf "%-50s %b\n" "$1" "${GREEN}OK${END}"
}

print_ko() {
    printf "%-50s %b\n" "$1" "${RED}KO${END}"
}

test_bash() {
    local command="$1"
    local bash_status minishell_status

    # Execute commands in parallel using background processes
    echo "$command" | bash >out_bash 2>err_bash &
    local bash_pid=$!

    echo "$command" | ./minishell >out_minishell 2>err_minishell &
    local minishell_pid=$!

    # Wait for both processes to complete
    wait $bash_pid
    bash_status=$?
    wait $minishell_pid
    minishell_status=$?

    # Compare outputs and cleanup in a single pass
    local has_error=0
    if ! diff out_bash out_minishell >/dev/null ||
        ! diff err_bash err_minishell >/dev/null ||
        [ $bash_status -ne $minishell_status ]; then
        print_ko "$command"
        has_error=1
    else
        print_ok "$command"
    fi

    # Cleanup temporary files
    rm -f out_{bash,minishell} err_{bash,minishell}
    return $has_error
}

# Test commands array
readonly commands=(
    "echo hello"
    "echo world"
)

# Execute tests
for command in "${commands[@]}"; do
    test_bash "$command"
done
