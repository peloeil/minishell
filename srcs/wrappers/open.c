/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:51:25 by sota              #+#    #+#             */
/*   Updated: 2025/05/16 23:14:12 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

int	wrap_open(const char *file, int flag)
{
	int	fd;

	if ((flag & O_WRONLY) || (flag & O_RDWR))
		fd = open(file, flag, 0644);
	else
		fd = open(file, flag);
	if (fd == -1)
		return (error_return(file, strerror(errno)));
	return (fd);
}
