/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 03:10:27 by sota              #+#    #+#             */
/*   Updated: 2024/06/27 01:40:58 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include <libft/ft_string.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*res;
	size_t	alloc_size;

	alloc_size = count;
	if (__builtin_mul_overflow(alloc_size, size, &alloc_size))
		return (NULL);
	res = malloc(alloc_size);
	if (res == NULL)
		return (NULL);
	return (ft_memset(res, 0, alloc_size));
}
