/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:26:12 by sota              #+#    #+#             */
/*   Updated: 2025/05/08 21:16:42 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/wait.h>

static int	set_parent_fds(int in_fd, int out_fd)
{
	(void)in_fd;
	(void)out_fd;
	return (0);
}

int	parent_process(pid_t pid, int in_fd, int out_fd)
{
	int	status;

	if (set_parent_fds(in_fd, out_fd) == -1)
		return (-1);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (-1);
}
