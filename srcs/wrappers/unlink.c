/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlink.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:12:06 by sota              #+#    #+#             */
/*   Updated: 2025/05/16 18:13:27 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int	wrap_unlink(const char *path)
{
	int	ret;

	ret = unlink(path);
	if (ret == -1)
		return (error_return("unlink", strerror(errno)));
	return (0);
}
