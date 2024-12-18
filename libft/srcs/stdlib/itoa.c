/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 03:10:28 by sota              #+#    #+#             */
/*   Updated: 2024/06/27 01:41:39 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stddef.h>
#include <libft/ft_string.h>

static size_t	count_digit(int n)
{
	size_t	res;

	if (n == 0)
		return (1);
	if (n == INT_MIN)
		return (11);
	res = 0;
	if (n < 0)
	{
		n *= -1;
		res = 1;
	}
	while (n > 0)
	{
		n /= 10;
		res++;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	char	integer[12];
	int		is_neg;
	size_t	digit;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	ft_bzero(integer, 12);
	is_neg = n < 0;
	if (is_neg)
	{
		integer[0] = '-';
		n *= -1;
	}
	digit = count_digit(n);
	while (digit--)
	{
		integer[digit + (size_t)is_neg] = n % 10 + '0';
		n /= 10;
	}
	return (ft_strdup(integer));
}
