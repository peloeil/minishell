/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 21:30:14 by marvin            #+#    #+#             */
/*   Updated: 2025/05/13 21:30:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_string.h>
#include <minishell/minishell.h>
#include <libft/ft_stdio.h>
#include <stdlib.h>
#include <libft/ft_ctype.h>
#include <libft/ft_stdlib.h>

int	is_numeric_argument(const char *str)
{
	int	i;

	if (!str || *str == '\0')
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	builtin_exit(int fd, char *argv[])
{
	int	argc;
	int	status;

	argc = count_argv(argv);
	ft_dprintf(fd, "logout\n");
	if (argc == 1)
		exit(0);
	if (!is_numeric_argument(argv[1]))
	{
		ft_dprintf(fd, "-minishell: exit: %s: \
			numeric argument required\n", argv[1]);
		exit(2);
	}
	if (argc > 2)
	{
		ft_dprintf(fd, "-minishell: exit: too many arguments\n");
		return (1); // 終了しない
	}
	status = ft_atoi(argv[1]);
	exit(status & 0xFF);
}
