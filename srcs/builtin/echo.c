/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 05:28:19 by yonuma            #+#    #+#             */
/*   Updated: 2025/05/27 17:58:01 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <minishell/execute.h>
#include <libft/ft_stdio.h>
#include <stdlib.h>

static int	is_n_option(const char *str)
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

static int	skip_n_option(char **argv, int *i)
{
	int	n_option;

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

	(void)envp;
	if (ft_str_new(&str))
		return (STATUS_ERRORS);
	i = 1;
	n_option = skip_n_option(argv, &i);
	while (argv[i])
	{
		if (ft_str_push_str(&str, argv[i]) == -1
			|| (argv[i + 1] != NULL && ft_str_push(&str, ' ') == -1))
			return (STATUS_ERRORS);
		i++;
	}
	if (!n_option && ft_str_push(&str, '\n') == -1)
		return (STATUS_ERRORS);
	i = ft_dprintf(fd, "%s", str.str);
	free(str.str);
	if (i < 0)
		return (STATUS_ERRORS);
	return (STATUS_SUCCESS);
}
