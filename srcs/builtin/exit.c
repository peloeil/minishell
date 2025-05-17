/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 21:30:14 by marvin            #+#    #+#             */
/*   Updated: 2025/05/15 04:19:52 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_ctype.h>
#include <libft/ft_stdio.h>
#include <libft/ft_stdlib.h>
#include <libft/ft_string.h>
#include <limits.h>
#include <minishell/minishell.h>

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

long	ft_atoilong(const char *str)
{
	size_t	i;
	long	res;
	long	flow;

	i = 0;
	flow = LONG_MAX;
	res = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			flow = LONG_MIN;
	while (ft_isdigit(str[i]))
	{
		if (__builtin_mul_overflow(res, 10, &res) || (flow > 0
				&& __builtin_add_overflow(res, str[i] - '0', &res)) || (flow < 0
				&& __builtin_sub_overflow(res, str[i] - '0', &res)))
			return (-1);
		i++;
	}
	return (res);
}

int	builtin_exit(int fd, char **argv, t_envp **envp)
{
	int		argc;
	int		status;
	long	test;

	// char	*value;
	(void)envp;
	argc = count_argv(argv);
	if (argc >= 2)
		test = ft_atoilong(argv[1]);
	ft_dprintf(fd, "logout\n");
	// 引数なしのexitの場合は、ms_envp内の？を参照
	if (argc == 1)
	{
		ft_printf("終了ステータスは？をみる\n");
		return (2);
	}
	// argv[1]が数字以外の場合と、数字がLONG_MAX＋１以上
	if (!is_numeric_argument(argv[1]) || test == -1)
	{
		ft_dprintf(fd, "-minishell: exit: %s: %s\n", argv[1], NUMERIC);
		ft_printf("終了ステータス：２\n");
		return (2);
		// exit(2);
	}
	// argv[1]が数字 ∧ 長い場合
	if (argc > 2)
	{
		ft_dprintf(fd, "%s\n", TOO_MANY);
		// ? に１を入れる
		return (1); // 終了しない
	}
	status = ft_atoi(argv[1]);
	ft_printf("終了ステータス: %d\n", status & 0xFF);
	// exit(status & 0xFF);
	return (0);
}
