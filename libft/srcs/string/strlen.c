/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 00:54:15 by sota              #+#    #+#             */
/*   Updated: 2024/06/27 01:45:46 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_string.h>
#include <stdint.h>
#include <stddef.h>

static __inline __attribute__((__always_inline__))
t_op	find_zero_low(t_op x)
{
	t_op	himagic;
	t_op	lomagic;

	himagic = (t_op)(-1) / 0xff * 0x80;
	lomagic = (t_op)(-1) / 0xff * 0x01;
	return ((x - lomagic) & ~x & himagic);
}

static __inline __attribute__((__always_inline__))
t_op	find_zero_all(t_op x)
{
	t_op	mask;

	mask = (t_op)(-1) / 0xff * 0x7f;
	return (~(((x & mask) + mask) | x | mask));
}

static __inline __attribute__((__always_inline__))
t_op	shift_find(t_op word, uintptr_t s)
{
	return (word >> ((s & (sizeof(word) - 1)) << 3));
}

static __inline __attribute__((__always_inline__))
size_t	index_first(t_op word)
{
	return (__builtin_ctzl(word) >> 3);
}

__attribute__((no_sanitize_address))
size_t	ft_strlen(const char *s)
{
	uintptr_t	s_int;
	t_op		*word_ptr;
	t_op		word;
	t_op		mask;

	s_int = (uintptr_t)s;
	word_ptr = (t_op *)((uintptr_t)(s_int) & -(uintptr_t)(sizeof(t_op)));
	word = *word_ptr;
	mask = shift_find(find_zero_all(word), s_int);
	if (mask != 0)
		return (index_first(mask));
	while (1)
	{
		word = *++word_ptr;
		if (find_zero_low(word) != 0)
			break ;
	}
	return (((const char *)word_ptr) + index_first(find_zero_low(word)) - s);
}
