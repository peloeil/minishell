/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 09:03:16 by marvin            #+#    #+#             */
/*   Updated: 2025/05/29 02:48:37 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <minishell/execute.h>
#include <libft/ft_stdio.h>
#include <libft/ft_string.h>
#include <stdlib.h>

int	count_argv(char **argv)
{
	int	count;

	count = 0;
	while (argv[count] != NULL)
		count++;
	return (count);
}

int	make_str(int is_double, t_string *str, const char *key, const char *value)
{
	int	status;

	status = 0;
	if (value == NULL)
		value = "";
	if (is_double == 0)
	{
		status |= ft_str_push_str(str, key);
		status |= ft_str_push_str(str, "=");
		status |= ft_str_push_str(str, value);
		status |= ft_str_push_str(str, "\n");
		return (status);
	}
	status |= ft_str_push_str(str, key);
	status |= ft_str_push_str(str, "=\"");
	status |= ft_str_push_str(str, value);
	status |= ft_str_push_str(str, "\"\n");
	return (status);
}
