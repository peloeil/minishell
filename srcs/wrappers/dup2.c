/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:17:13 by sota              #+#    #+#             */
/*   Updated: 2025/05/27 20:47:03 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int	wrap_dup2(int oldfd, int newfd)
{
	int	ret;

	ret = dup2(oldfd, newfd);
	if (ret == -1)
		return (error_return(-1, "dup2", strerror(errno)));
	return (0);
}
