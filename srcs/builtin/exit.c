/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 21:30:14 by marvin            #+#    #+#             */
/*   Updated: 2025/06/03 21:51:26 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <minishell/execute.h>
#include <libft/ft_ctype.h>
#include <libft/ft_stdio.h>
#include <libft/ft_stdlib.h>
#include <limits.h>
#include <stdlib.h>

#define MASK_EXIT 0xFF

long	is_numeric_argument(const char *str)
{
	long	i;

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

static int	str_to_status(const char *str)
{
	size_t	i;
	int		sign;
	long	res;

	i = 0;
	sign = 1;
	res = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -1;
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]))
			return (-1);
		if (sign > 0 && res > (LONG_MAX - str[i] + '0') / 10)
			return (-1);
		if (sign < 0 && res < (LONG_MIN + str[i] - '0') / 10)
			return (-1);
		res = res * 10 + sign * (str[i] - '0');
		i++;
	}
	return ((res % MASK_EXIT + MASK_EXIT) % MASK_EXIT);
}

int	builtin_exit(int fd, char **argv, t_envp **envp)
{
	int	argc;
	int	status;

	(void)fd;
	argc = count_argv(argv);
	if (argc == 1)
		return (-2);
	status = str_to_status(argv[1]);
	if (status == -1)
	{
		ft_dprintf(STDERR_FILENO,
			"minishell: exit: %s: numeric argument required\n", argv[1]);
		if (update_exit_status(STATUS_MISUSE, envp) == -1)
			return (STATUS_ERRORS);
		return (-2);
	}
	if (argc > 2)
	{
		ft_dprintf(STDERR_FILENO, "%s\n", TOO_MANY);
		return (STATUS_ERRORS);
	}
	if (update_exit_status(status, envp) == -1)
		return (STATUS_ERRORS);
	return (-2);
}
