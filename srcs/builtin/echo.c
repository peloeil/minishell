/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonuma <yonuma@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-16 05:28:19 by yonuma            #+#    #+#             */
/*   Updated: 2025-04-16 05:28:19 by yonuma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <stdlib.h>
#include <libft/ft_stdio.h>
#include <libft/libft.h>

int calc_argc(char *argv[])
{
    int i;

    i = 0;
    while (argv[i])
        i++;
    return (i);
}

int echo(int fd, char *argv[])
{
	int n_option;
	int argc;
	int i;

	n_option = 0;
	argc = calc_argc(argv);
	i = 1;
	while (ft_strcmp(argv[i], "-n") == 0)
	{
		n_option = 1;
		i++;
	}
	while (i < argc)
	{
		ft_dprintf(fd, "%s", argv[i]);
		if (i < argc - 1)
			ft_dprintf(fd, " ");
		i++;
	}
	if (!n_option)
		ft_dprintf(fd, "\n");
	return (0);
}
