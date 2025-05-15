/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 05:28:19 by yonuma            #+#    #+#             */
/*   Updated: 2025/05/15 04:18:38 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <libft/ft_stdio.h>
#include <libft/libft.h>
#include <stdlib.h>

int	echo(int fd, char **argv, t_envp **envp)
{
	int			n_option;
	int			i;
	t_string	str;

	(void)envp;
	if (ft_str_new(&str))
		return (1);
	n_option = 0;
	i = 1;
	while (argv[i] != NULL)
	{
		if (ft_strncmp(argv[i], "-n", 2) == 0)
			n_option = 1;
		else if (ft_str_push_str(&str, argv[i]) == -1
			|| (argv[i + 1] != NULL && ft_str_push(&str, ' ') == -1))
			return (1);
		i++;
	}
	if (n_option != 1 && ft_str_push(&str, '\n') == -1)
		return (1);
	i = ft_dprintf(fd, "%s", str.str);
	free(str.str);
	if (i < 0)
		return (1);
	return (0);
}
