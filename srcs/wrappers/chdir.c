/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonuma <yonuma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 21:25:51 by sota              #+#    #+#             */
/*   Updated: 2025/06/28 21:55:43 by yonuma           ###   ########.fr       */
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
		ft_dprintf(STDERR_FILENO, "minishell: cd: %s: %s\n", path,
			strerror(errno));
		return (-1);
	}
	return (0);
}
