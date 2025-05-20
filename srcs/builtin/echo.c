/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 05:28:19 by yonuma            #+#    #+#             */
/*   Updated: 2025/05/22 00:10:31 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <libft/ft_stdio.h>
#include <libft/libft.h>
#include <stdlib.h>

int	is_n_option(const char *str)
{
	int	i;

	if (str == NULL || str[0] != '-')
		return (0);
	i = 1;
	if (!str[1])
		return (0);
	while (str[i])
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	skip_n_option(char **argv, int *i)
{
	int	n_option;

	(void)envp;
	n_option = 0;
	while (argv[*i] && is_n_option(argv[*i]))
	{
		n_option = 1;
		(*i)++;
	}
	return (n_option);
}

int	echo(int fd, char **argv, t_envp **envp)
{
	int			n_option;
	int			i;
	t_string	str;

	if (ft_str_new(&str))
		return (EXIT_FAILURE);
	i = 1;
	n_option = skip_n_option(argv, &i);
	while (argv[i])
	{
		if (ft_str_push_str(&str, argv[i]) == -1
			|| (argv[i + 1] != NULL && ft_str_push(&str, ' ') == -1))
			return (EXIT_FAILURE);
		i++;
	}
	if (n_option != 1 && ft_str_push(&str, '\n') == -1)
		return (EXIT_FAILURE);
	i = ft_dprintf(fd, "%s", str.str);
	free(str.str);
	if (i < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
