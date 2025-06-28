/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:25:51 by sota              #+#    #+#             */
/*   Updated: 2025/06/28 16:41:31 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <libft/ft_stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int	wrap_chdir(const char *path)
{
	int	ret;

	ret = chdir(path);
	if (ret == -1)
	{
		ft_dprintf(STDERR_FILENO, "minishell: cd: %s: %s\n", path, strerror(errno));
		return (-1);
	}
	return (0);
}
