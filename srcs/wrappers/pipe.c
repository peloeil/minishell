/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 05:12:04 by sota              #+#    #+#             */
/*   Updated: 2025/05/15 05:13:33 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int	wrap_pipe(int *pipefd)
{
	int	ret;

	ret = pipe(pipefd);
	if (ret == -1)
		return (error_return("pipe", strerror(errno)));
	return (0);
}
