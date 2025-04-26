#include <minishell/minishell.h>
#include <libft/ft_string.h>
#include <libft/ft_stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int	handle_builtin_command(char **argv, struct minishell_envp *envp)
{
	if (ft_strcmp(argv[0], "pwd") == 0)
		return pwd();
	if (ft_strcmp(argv[0], "export") == 0)
		return export(argv, envp);
	return (-2);
}

int	handle_external_command(char **argv, const char **envp)
{
	char	*cmd_path;
	int		status;
	pid_t	pid;

	status = set_cmd_path(&cmd_path, argv[0], envp);
	if (status == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		free(cmd_path);
		return (-1);
	}
	if (pid == 0)
	{
		execve(cmd_path, argv, (char **)envp);
		exit(1);
	}
	wait(NULL);
	free(cmd_path);
	return (0);
}

int	eval_cmd(const char *cmd, t_minishell_envp *minishell_envp, const char **envp)
{
	int		status;
	char	**argv;

	argv = ft_split(cmd, ' ');
	if (!argv)
		return (-1);
	status = handle_builtin_command(argv, minishell_envp);
	if (status == -2)
		status = handle_external_command(argv, envp);
	free_strs((const char **)argv);
	return (status);
}
