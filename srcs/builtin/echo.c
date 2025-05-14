/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 05:28:19 by yonuma            #+#    #+#             */
/*   Updated: 2025/05/11 20:45:28 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <stdlib.h>
#include <libft/ft_stdio.h>
#include <libft/libft.h>

int	echo(int fd, char *argv[])
{
	int	n_option;
	int	i;
	int	argc;

	n_option = 0;
	i = 1;
	argc = count_argv(argv);
	while (i < argc)
	{
		if (ft_strncmp(argv[i], "-n", 2) == 0)
			n_option = 1;
		else
		{
			ft_dprintf(fd, "%s", argv[i]);
			if (i < argc - 1)
				ft_dprintf(fd, " ");
		}
		i ++;
	}
	if (n_option != 1)
		ft_dprintf(fd, "\n");
	return (0);
}
