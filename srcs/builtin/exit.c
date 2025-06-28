/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 21:30:14 by marvin            #+#    #+#             */
/*   Updated: 2025/06/28 19:16:45 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <minishell/execute.h>
#include <libft/ft_ctype.h>
#include <libft/ft_stdio.h>
#include <libft/ft_string.h>
#include <limits.h>
#include <stdlib.h>

#define MASK_EXIT 0x100

static int	str_to_status(char *str)
{
	size_t	i;
	long	sign;
	long	res;
	int		invalid;

	str = ft_strtrim(str, " ");
	if (str == NULL)
		return (-1);
	i = 0;
	sign = 1 - 2 * ((str[i] == '-' || str[i] == '+') && str[i++] == '-');
	invalid = (str[i] == '\0');
	res = 0;
	while (!invalid && str[i] != '\0')
	{
		if (!ft_isdigit(str[i])
			|| (sign > 0 && res > (LONG_MAX - str[i] + '0') / 10)
			|| (sign < 0 && res < (LONG_MIN + str[i] - '0') / 10))
			invalid = 1;
		res = res * 10 + sign * (str[i] - '0');
		i++;
	}
	free(str);
	if (invalid)
		return (-1);
	return (((int)res % MASK_EXIT + MASK_EXIT) % MASK_EXIT);
}

int	builtin_exit(int fd, char **argv, t_envp **envp)
{
	int	argc;
	int	status;

	(void)fd;
	ft_dprintf(STDERR_FILENO, "exit\n");
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
		return (error_return(STATUS_ERRORS, "exit", "too many arguments"));
	if (update_exit_status(status, envp) == -1)
		return (STATUS_ERRORS);
	return (-2);
}
