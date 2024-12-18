/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   with_capacity.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 19:09:08 by sota              #+#    #+#             */
/*   Updated: 2024/12/03 03:39:53 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/std_string.h>
#include <stdlib.h>

static size_t	next_power_of_two(size_t n)
{
	if ((n >> (sizeof(size_t) - 1)) & 1)
		return (n);
	n--;
	n |= n >> 1;
	n |= n >> 2;
	n |= n >> 4;
	n |= n >> 8;
	n |= n >> 16;
	if (sizeof(size_t) == 64)
		n |= n >> 32;
	n++;
	return (n);
}

int	ft_str_with_capacity(t_string *str, size_t capacity)
{
	size_t	reserve;

	reserve = next_power_of_two(capacity + 1) - 1;
	str->len = 0;
	str->capacity = reserve;
	str->str = (char *)malloc(sizeof(char) * (reserve + 1));
	if (str->str == NULL)
		return (-1);
	str->str[0] = '\0';
	return (0);
}
