/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reserve.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 22:35:19 by sota              #+#    #+#             */
/*   Updated: 2025/05/14 11:46:42 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_string.h>
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

int	ft_str_reserve(t_string *str, size_t additional)
{
	char	*new_str;
	size_t	reserve;

	if (str->len + additional <= str->capacity)
		return (0);
	reserve = next_power_of_two(str->len + additional + 1) - 1;
	new_str = (char *)malloc(sizeof(char) * (reserve + 1));
	if (new_str == NULL)
	{
		free(str->str);
		return (-1);
	}
	ft_memcpy(new_str, str->str, str->capacity + 1);
	free(str->str);
	str->str = new_str;
	str->capacity = reserve;
	return (0);
}
