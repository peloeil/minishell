/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_int.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 22:43:19 by sota              #+#    #+#             */
/*   Updated: 2024/12/09 02:29:24 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/std_string.h>
#include <libft/ft_string.h>
#include <libft/internal/__printf.h>
#include <limits.h>

static size_t	digit_uint(unsigned int n)
{
	size_t	res;

	if (n == 0)
		return (1);
	res = 0;
	while (n > 0)
	{
		n /= 10;
		res++;
	}
	return (res);
}

int	__push_int(t_string *str, size_t size, int n)
{
	char	integer[12];
	int		is_neg;
	size_t	digit;

	if (n == INT_MIN)
		return (__push_str(str, size, "-2147483648"));
	ft_bzero(integer, 12);
	is_neg = n < 0;
	if (is_neg)
	{
		integer[0] = '-';
		n *= -1;
	}
	digit = digit_uint(n);
	while (digit--)
	{
		integer[digit + (size_t)is_neg] = n % 10 + '0';
		n /= 10;
	}
	return (__push_str(str, size, integer));
}
