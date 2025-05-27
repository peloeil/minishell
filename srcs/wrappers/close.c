/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 15:37:52 by sota              #+#    #+#             */
/*   Updated: 2025/05/27 20:47:55 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

static int	already_closed(int fd)
{
	int	newfd;

	newfd = dup(fd);
	if (newfd == -1 && errno == EBADF)
		return (1);
	if (newfd == -1)
		return (error_return(0, "dup", strerror(errno)));
	close(newfd);
	return (0);
}

int	wrap_close(int *fd, int afterfd)
{
	if (*fd == -1)
		return (0);
	if (*fd == afterfd)
		return (0);
	if (already_closed(*fd))
	{
		*fd = afterfd;
		return (0);
	}
	close(*fd);
	*fd = afterfd;
	return (0);
}
