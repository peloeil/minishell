#include <minishell/minishell.h>
#include <libft/ft_stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Helper function to capture the output of pwd
char *capture_pwd_output()
{
    FILE *fp;
    char *output = NULL;
    size_t len = 0;

    fp = popen("./minishell -c pwd", "r"); // Run the minishell pwd command
    if (fp == NULL)
    {
        perror("popen failed");
        return NULL;
    }

    getline(&output, &len, fp); // Capture the output
    pclose(fp);

    // Remove trailing newline
    if (output && output[strlen(output) - 1] == '\n')
        output[strlen(output) - 1] = '\0';

    return output;
}

int test_pwd_no_arguments()
{
    char *argv[] = {"pwd", NULL};
    char *expected_output = getcwd(NULL, 0); // Get the expected output
    char *actual_output;
    int result;

    // Directly call the pwd function
    result = pwd(1, argv);

    // Capture the output from the function
    actual_output = getcwd(NULL, 0);

    if (result != 0 || strcmp(expected_output, actual_output) != 0)
    {
        printf("test_pwd_no_arguments: FAILED\n");
        printf("  Expected: %s\n", expected_output);
        printf("  Got: %s\n", actual_output);
        free(expected_output);
        free(actual_output);
        return 1;
    }

    printf("test_pwd_no_arguments: PASSED\n");
    free(expected_output);
    free(actual_output);
    return 0;
}

int test_pwd_too_many_arguments()
{
    char *argv[] = {"pwd", "extra_arg", NULL};
    int result = pwd(2, argv);

    if (result != 1)
    {
        printf("test_pwd_too_many_arguments: FAILED\n");
        printf("  Expected: 1\n");
        printf("  Got: %d\n", result);
        return 1;
    }

    printf("test_pwd_too_many_arguments: PASSED\n");
    return 0;
}

int main()
{
    int failed = 0;

    printf("Running tests...\n");

    failed += test_pwd_no_arguments();
    failed += test_pwd_too_many_arguments();

    if (failed == 0)
    {
        printf("All tests passed!\n");
    }
    else
    {
        printf("%d test(s) failed.\n", failed);
    }

    return failed;
}