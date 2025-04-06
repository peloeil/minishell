#include <minishell/minishell.h>
#include <libft/ft_stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// テスト1: 引数なしでpwdを呼び出す
int test_pwd_no_arguments()
{
    char *argv[] = {"pwd", NULL};
    char *expected = getcwd(NULL, 0);
    int result = pwd(1, argv);

    if (result != 0)
    {
        printf("test_pwd_no_arguments: FAILED (pwd returned %d)\n", result);
        free(expected);
        return 1;
    }

    printf("test_pwd_no_arguments: PASSED (Output: %s)\n", expected);
    free(expected);
    return 0;
}

// テスト2: 引数が多すぎる場合
int test_pwd_too_many_arguments()
{
    char *argv[] = {"pwd", "extra_arg", NULL};
    int result = pwd(2, argv);

    if (result != 1)
    {
        printf("test_pwd_too_many_arguments: FAILED (Expected 1, got %d)\n", result);
        return 1;
    }

    printf("test_pwd_too_many_arguments: PASSED\n");
    return 0;
}

// テスト実行
int main()
{
    int failed = 0;

    printf("Running pwd tests...\n");

    failed += test_pwd_no_arguments();
    failed += test_pwd_too_many_arguments();

    if (failed == 0)
        printf("All tests passed!\n");
    else
        printf("%d test(s) failed.\n", failed);

    return failed;
}
