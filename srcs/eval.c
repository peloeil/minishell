/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:11:44 by marvin            #+#    #+#             */
/*   Updated: 2025/05/03 00:35:08 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <libft/ft_string.h>
#include <libft/ft_stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int	handle_builtin_command(char **argv, t_envp *envp)
{
	if (ft_strcmp(argv[0], "pwd") == 0)
		return (pwd());
	if (ft_strcmp(argv[0], "export") == 0)
		return (export(STDOUT_FILENO, argv, envp));
	if (ft_strcmp(argv[0], "env") == 0)
		return (env(STDOUT_FILENO, envp));
	return (-2);
}

int	handle_external_command(char **argv, const t_envp *envp)
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
		execve(cmd_path, argv, NULL);
		exit(1);
	}
	wait(NULL);
	free(cmd_path);
	return (0);
}

int	eval_cmd(const char *cmd, t_envp *ms_envp)
{
	int		status;
	char	**argv;

	argv = ft_split(cmd, ' ');
	if (argv == NULL)
		return (-1);
	status = handle_builtin_command(argv, ms_envp);
	if (status == -2)
		status = handle_external_command(argv, ms_envp);
	free_strs((const char **)argv);
	return (status);
}
