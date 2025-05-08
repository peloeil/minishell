/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:23:41 by sota              #+#    #+#             */
/*   Updated: 2025/05/08 23:38:50 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <minishell/parser.h>
#include <minishell/execute.h>
#include <libft/ft_string.h>
#include <unistd.h>
#include <stdlib.h>

static int	set_child_fds(int in_fd, int out_fd)
{
	if (in_fd != STDIN_FILENO)
	{
		if (dup2(in_fd, STDIN_FILENO) == -1)
			return (-1);
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		if (dup2(out_fd, STDOUT_FILENO) == -1)
			return (-1);
		close(out_fd);
	}
	return (0);
}


int	child_process(
				t_arg_list *args,
				int in_fd,
				int out_fd,
				t_envp *ms_envp)
{
	char	**argv;
	char	**envp;

	if (set_child_fds(in_fd, out_fd) == -1)
		return (-1);
	if (make_argv(&argv, args) == -1)
		return (-1);
	if (make_envp(&envp, ms_envp) == -1)
	{
		free_strs(argv);
		return (-1);
	}
	free(argv[0]);
	if (set_cmd_path(&argv[0], args->content, ms_envp) == -1)
	{
		free_strs(argv);
		free_strs(envp);
		return (-1);
	}
	execve(argv[0], argv, envp);
	free_strs(argv);
	free_strs(envp);
	return (-1);
}
