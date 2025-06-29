/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 21:52:36 by sota              #+#    #+#             */
/*   Updated: 2025/06/28 21:58:47 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <sys/wait.h>
#include <string.h>
#include <errno.h>

int	wrap_wait(int *wstatus)
{
	pid_t	pid;

	while (1)
	{
		pid = wait(wstatus);
		if (pid == -1 && errno == EINTR)
			continue ;
		break ;
	}
	if (pid == -1)
		return (error_return(-1, "wait", strerror(errno)));
	return (pid);
}
