/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcpy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 03:10:52 by sota              #+#    #+#             */
/*   Updated: 2024/12/12 20:23:25 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dst_str;
	char	*src_str;

	i = 0;
	dst_str = (char *)dst;
	src_str = (char *)src;
	while (i < n)
	{
		dst_str[i] = src_str[i];
		i++;
	}
	return (dst);
}
