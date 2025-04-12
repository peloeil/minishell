#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 標準出力の1行目を読み取る関数（改行も含めて返す）
char *get_command_output(const char *cmd)
{
    FILE *fp = popen(cmd, "r");
    if (!fp)
    {
        perror("popen");
        return NULL;
    }

    char *buffer = malloc(1024);
    if (!fgets(buffer, 1024, fp))
    {
        perror("fgets");
        pclose(fp);
        free(buffer);
        return NULL;
    }

    pclose(fp);
    return buffer;
}

int test_pwd_no_arguments()
{
    char *expected = get_command_output("pwd");
    char *actual = get_command_output("echo pwd | ./minishell");

    if (!expected || !actual)
    {
        free(expected);
        free(actual);
        return 1;
    }

    // 改行を削除して比較
    expected[strcspn(expected, "\n")] = '\0';
    actual[strcspn(actual, "\n")] = '\0';

    if (strcmp(expected, actual) != 0)
    {
        printf("test_pwd_no_arguments: FAILED\nExpected: [%s]\nActual:   [%s]\n", expected, actual);
        free(expected);
        free(actual);
        return (1);
    }

    printf("test_pwd_no_arguments: PASSED (Output: %s)\n", actual);
    free(expected);
    free(actual);
    return 0;
}

int main()
{
    int failed = 0;
    printf("Running pwd tests...\n");

    failed += test_pwd_no_arguments();

    if (failed == 0)
        printf("All tests passed!\n");
    else
        printf("%d test(s) failed.\n", failed);

    return failed;
}
