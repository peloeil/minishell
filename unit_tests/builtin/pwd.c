#include <minishell/minishell.h>
#include <libft/ft_stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// テスト1: 引数なしでpwdを呼び出す
int test_pwd_no_arguments()
{
    char *expected = getcwd(NULL, 0);
    if (!expected)
    {
        perror("getcwd");
        return 1;
    }

    // Use popen to capture the output of the pwd function
    FILE *fp = popen("./minishell_pwd", "r");
    if (!fp)
    {
        perror("popen");
        free(expected);
        return 1;
    }

    char actual[1024];
    if (!fgets(actual, sizeof(actual), fp))
    {
        perror("fgets");
        pclose(fp);
        free(expected);
        return 1;
    }
    pclose(fp);

    // Remove trailing newline from actual output
    actual[strcspn(actual, "\n")] = '\0';

    if (strcmp(expected, actual) != 0)
    {
        printf("test_pwd_no_arguments: FAILED (Expected: %s, Actual: %s)\n", expected, actual);
        free(expected);
        return 1;
    }

    printf("test_pwd_no_arguments: PASSED (Output: %s)\n", actual);
    free(expected);
    return 0;
}

// テスト実行
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
