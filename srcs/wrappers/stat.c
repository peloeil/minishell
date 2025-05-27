/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stat.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:10:49 by sota              #+#    #+#             */
/*   Updated: 2025/05/27 20:47:30 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

int	wrap_stat(const char *path, struct stat *statbuf)
{
	int	ret;

	ret = stat(path, statbuf);
	if (ret == -1)
		return (error_return(-1, path, strerror(errno)));
	return (0);
}
