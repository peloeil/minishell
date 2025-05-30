/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:25:51 by sota              #+#    #+#             */
/*   Updated: 2025/05/27 21:27:58 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int	wrap_chdir(const char *path)
{
	int	ret;

	ret = chdir(path);
	if (ret == -1)
		return (error_return(-1, "chdir", strerror(errno)));
	return (0);
}
