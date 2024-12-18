/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_uint.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 22:43:19 by sota              #+#    #+#             */
/*   Updated: 2024/12/09 02:46:02 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/std_string.h>
#include <libft/ft_string.h>
#include <libft/internal/__printf.h>

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

int	__push_uint(t_string *str, size_t size, unsigned int n)
{
	char	integer[12];
	size_t	digit;

	ft_bzero(integer, 12);
	digit = digit_uint(n);
	while (digit--)
	{
		integer[digit] = n % 10 + '0';
		n /= 10;
	}
	return (__push_str(str, size, integer));
}
