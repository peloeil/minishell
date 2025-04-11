/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 18:05:59 by sota              #+#    #+#             */
/*   Updated: 2025/03/12 22:23:45 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <libft/ft_string.h>
#include <libft/ft_stdio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int	builtin()

int	eval_cmd(const char *cmd, const char **envp)
{
	int		status;
	char	**argv;
	char	*cmd_path;
	pid_t	pid;

	argv = ft_split(cmd, ' ');
	if (argv == NULL)
		return (-1);
	if (ft_strcmp(argv[0], "pwd") == 0)
    {
        status = pwd();
        free_strs((const char **)argv);
        return (status);
    }
	status = set_cmd_path(&cmd_path, argv[0], envp);
	if (status == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		execve(cmd_path, argv, (char **)envp);
		exit(1);
	}
	wait(NULL);
	free_strs((const char **)argv);
	free(cmd_path);
	return (status);
}
