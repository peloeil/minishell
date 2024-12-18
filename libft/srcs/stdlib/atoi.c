/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 03:10:25 by sota              #+#    #+#             */
/*   Updated: 2024/12/18 00:34:32 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stddef.h>
#include <libft/ft_ctype.h>

int	ft_atoi(const char *str)
{
	size_t	i;
	long	res;
	long	limit;

	i = 0;
	limit = LONG_MAX;
	res = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			limit = LONG_MIN;
	}
	while (ft_isdigit(str[i]))
	{
		if (__builtin_mul_overflow(res, 10, &res)
			|| (limit > 0 && __builtin_add_overflow(res, str[i] - '0', &res))
			|| (limit < 0 && __builtin_sub_overflow(res, str[i] - '0', &res)))
			return (limit);
		i++;
	}
	return (res);
}
