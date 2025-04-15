#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 8192
#define MAX_LINES 1024

// コマンド実行結果を文字列で取得
char *get_full_output(const char *cmd) {
    FILE *fp = popen(cmd, "r");
    if (!fp) {
        perror("popen");
        return NULL;
    }

    char *output = malloc(BUFFER_SIZE);
    if (!output) {
        perror("malloc");
        pclose(fp);
        return NULL;
    }

    output[0] = '\0';
    char temp[1024];
    while (fgets(temp, sizeof(temp), fp) != NULL) {
        strncat(output, temp, BUFFER_SIZE - strlen(output) - 1);
    }

    pclose(fp);
    return output;
}

// 行末トリム関数（空白・改行除去）
void trim_newline(char *line) {
    int len = strlen(line);
    while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == ' ')) {
        line[--len] = '\0';
    }
}

// "_=" で始まる行を無視する判定
int is_ignore_line(const char *line) {
    return strncmp(line, "_=", 2) == 0;
}

// 出力を行ごとに順番に比較し、差分を表示
int compare_outputs_line_by_line(const char *a, const char *b) {
    char *a_copy = strdup(a);
    char *b_copy = strdup(b);
    if (!a_copy || !b_copy) {
        perror("strdup");
        free(a_copy);
        free(b_copy);
        return 1;
    }

    char *a_lines[MAX_LINES], *b_lines[MAX_LINES];
    int a_count = 0, b_count = 0;

    char *token = strtok(a_copy, "\n");
    while (token && a_count < MAX_LINES) {
        trim_newline(token);
        a_lines[a_count++] = token;
        token = strtok(NULL, "\n");
    }

    token = strtok(b_copy, "\n");
    while (token && b_count < MAX_LINES) {
        trim_newline(token);
        b_lines[b_count++] = token;
        token = strtok(NULL, "\n");
    }

    int failed = 0;
    int i = 0, j = 0, line_num = 1;

    while (i < a_count && j < b_count) {
        if (is_ignore_line(a_lines[i])) { i++; line_num++; continue; }
        if (is_ignore_line(b_lines[j])) { j++; line_num++; continue; }

        if (strcmp(a_lines[i], b_lines[j]) != 0) {
            printf("❌ 行 %d が一致しません\n", line_num);
            printf("  Expected: \"%s\"\n", a_lines[i]);
            printf("  Actual  : \"%s\"\n", b_lines[j]);
            failed = 1;
        } else {
            printf("✅ 行 %d: \"%s\"\n", line_num, a_lines[i]);
        }

        i++;
        j++;
        line_num++;
    }

    // 片方がまだ残ってる
    if (i < a_count || j < b_count) {
        printf("❌ 行数が一致しません: expected %d, actual %d\n", a_count, b_count);
        failed = 1;
    }

    free(a_copy);
    free(b_copy);
    return failed;
}

// テスト関数：env単体出力を比較
int test_env_no_args() {
    char *expected = get_full_output("env");
    char *actual = get_full_output("echo env | ./minishell");

    if (!expected || !actual) {
        fprintf(stderr, "出力取得に失敗しました\n");
        free(expected);
        free(actual);
        return 1;
    }

    printf("📤 比較開始:\n");
    int result = compare_outputs_line_by_line(expected, actual);

    if (result != 0) {
        printf("❌ test_env_no_args: FAILED\n");
    } else {
        printf("✅ test_env_no_args: PASSED\n");
    }

    free(expected);
    free(actual);
    return result;
}

int main() {
    int failed = 0;
    printf("🔍 Running env tests...\n");
    failed += test_env_no_args();

    if (failed == 0)
        printf("🎉 All tests passed!\n");
    else
        printf("❗ %d test(s) failed.\n", failed);

    return failed;
}
