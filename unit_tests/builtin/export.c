#include <libft/ft_string.h>
#include <libft/std_string.h>
#include <minishell/minishell.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 4096
#define READ_PIPE 0
#define WRITE_PIPE 1
#define MAX_NARGS 10

static t_string make_cmd_string(const char *cmd_name, char **args) {
    t_string cmd;
    ft_str_from(&cmd, "bash -c 'builtin ");
    ft_str_push_str(&cmd, cmd_name);
    for (int i = 0; args[i] != NULL; i++) {
        ft_str_push(&cmd, ' ');
        ft_str_push_str(&cmd, args[i]);
    }
    ft_str_push(&cmd, '\'');
    return cmd;
}

char *bash_builtin(const char *cmd_name, char **args) {
    t_string cmd = make_cmd_string(cmd_name, args);

    t_string buffer;
    ft_str_new(&buffer);

    FILE *fp = popen(cmd.str, "r");
    char tmp[BUF_SIZE];
    while (fgets(tmp, sizeof(tmp), fp) != NULL) {
        ft_str_push_str(&buffer, tmp);
    }
    free(cmd.str);
    pclose(fp);
    return buffer.str;
}

char *my_builtin(int (*builtin)(int, char **, t_envp *), char **args, t_envp *envp) {
    int pipefd[2];
    pipe(pipefd);

    builtin(pipefd[WRITE_PIPE], args, envp);
    close(pipefd[WRITE_PIPE]);

    t_string buffer;
    ft_str_new(&buffer);
    char tmp[BUF_SIZE];
    while (1) {
        ssize_t nbytes = read(pipefd[READ_PIPE], tmp, BUF_SIZE - 1);
        tmp[nbytes] = '\0';
        if (nbytes == 0) { break; }
        ft_str_push_str(&buffer, tmp);
    }
    close(pipefd[READ_PIPE]);

    return buffer.str;
}

static size_t next_len(const char *str, size_t start) {
    size_t len = 0;
    while (str[start + len] != '\0' && str[start + len] != '\n') {
        len++;
    }
    return len;
}

static void test(char **args, t_envp *envp) {
    char *expected = bash_builtin("export", args);
    char *actual = my_builtin(export, args, envp);

    int cmp = 0;
    size_t index = 0;
    while (expected[index] != '\0' && actual[index] != '\0') {
        size_t len = next_len(expected, index);
        if (len > next_len(actual, index)) { len = next_len(actual, index); }
        if (len == 0) { break; }
        cmp = strncmp(expected + index, actual + index, len);
        if (cmp != 0) { break; }
        index += len;
    }
    free(expected);
    free(actual);
    if (cmp != 0) { exit(1); }
}

t_envp *make_minishell_envp(char **envp) {
    t_envp *minishell_envp;
    t_envp *head;
    char *delimiter_pos;
    int i;

    minishell_envp = NULL;
    head = NULL;
    i = 0;
    while (envp[i]) {
        minishell_envp = malloc(sizeof(t_envp));
        if (!minishell_envp) return (NULL);
        delimiter_pos = ft_strchr(envp[i], '=');
        minishell_envp->key = ft_substr(envp[i], 0, delimiter_pos - envp[i]);
        minishell_envp->value = ft_strdup(delimiter_pos + 1);
        minishell_envp->exported = 1;
        minishell_envp->next = head;
        head = minishell_envp;
        i++;
    }
    return (head);
}

void free_minishell_envp(t_envp *envp) {
    while (envp != NULL) {
        t_envp *next = envp->next;
        free(envp->key);
        free(envp->value);
        free(envp);
        envp = next;
    }
}

int main(int argc, char **argv, char **envp) {
    (void)argc;
    (void)argv;

    char *args_array[][MAX_NARGS + 1] = {
        { NULL },
        { "a", NULL },
        { "a=b", NULL },
        { "a=b", "c=d", NULL },
    };

    t_envp *ms_envp = make_minishell_envp(envp);

    int ntests = sizeof(args_array) / sizeof(args_array[0]);
    for (int i = 0; i < ntests; i++) {
        test(args_array[i], ms_envp);
    }

    free_minishell_envp(ms_envp);
    return 0;
}
