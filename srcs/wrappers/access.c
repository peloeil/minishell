/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:10:49 by sota              #+#    #+#             */
/*   Updated: 2025/05/14 16:21:11 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

int	wrap_access(const char *path, int mode)
{
	int		ret;

	ret = access(path, mode);
	if (ret == -1 && errno == ENOENT && mode == F_OK)
		return (error_return(path, strerror(ENOENT)));
	if (ret == -1 && errno == EACCES && mode == X_OK)
		return (error_return(path, strerror(EACCES)));
	if (ret == -1)
		return (error_return("access", strerror(errno)));
	return (0);
}
