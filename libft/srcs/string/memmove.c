/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memmove.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 03:10:53 by sota              #+#    #+#             */
/*   Updated: 2024/12/12 20:46:35 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdint.h>
#include <libft/ft_string.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*dst_str;
	unsigned char	*src_str;

	if ((uintptr_t)dst <= (uintptr_t)src)
		return (ft_memcpy(dst, src, len));
	dst_str = (unsigned char *)dst;
	src_str = (unsigned char *)src;
	while (len--)
		dst_str[len] = src_str[len];
	return (dst);
}
