#include <libft/std_string.h>
#include <minishell/minishell.h>
#include <stdio.h>
#include <stdlib.h>
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

char *bash_builtin(const char *cmd_name, char **argv, t_envp **envp) {
    (void)envp;
    t_string cmd = make_cmd_string(cmd_name, argv);

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

char *my_builtin(int (*builtin)(int, char **, t_envp **), char **argv, t_envp **envp) {
    int pipefd[2];
    pipe(pipefd);

    builtin(pipefd[WRITE_PIPE], argv, envp);
    close(pipefd[WRITE_PIPE]);

    t_string buffer;
    ft_str_new(&buffer);
    char tmp[BUF_SIZE + 1];
    while (1) {
        ssize_t nbytes = read(pipefd[READ_PIPE], tmp, BUF_SIZE);
        tmp[nbytes] = '\0';
        if (nbytes == 0) { break; }
        ft_str_push_str(&buffer, tmp);
    }
    close(pipefd[READ_PIPE]);

    return buffer.str;
}
