/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_hex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 22:43:22 by sota              #+#    #+#             */
/*   Updated: 2024/12/09 02:45:44 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/internal/__printf.h>
#include <libft/std_string.h>
#include <stdint.h>

int	__push_hex(t_string *str, size_t size, uintptr_t n, int flag)
{
	char	*hex;
	int		shift;

	if (flag == AS_PTR && n == 0)
		return (__push_str(str, size, "(nil)"));
	hex = "0123456789abcdef";
	if (flag == AS_UP)
		hex = "0123456789ABCDEF";
	shift = 0;
	while ((n >> shift) >= 0x10)
		shift += 4;
	if (flag == AS_PTR && __push_str(str, size, "0x") == -1)
		return (-1);
	while (shift >= 0)
	{
		if (__push_ch(str, size, hex[(n >> shift) & 0x0f]) == -1)
			return (-1);
		shift -= 4;
	}
	return (0);
}
