/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 15:18:49 by sota              #+#    #+#             */
/*   Updated: 2025/05/27 21:29:50 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int	wrap_fork(void)
{
	int	ret;

	ret = fork();
	if (ret == -1)
		return (error_return(-1, "fork", strerror(errno)));
	return (ret);
}
