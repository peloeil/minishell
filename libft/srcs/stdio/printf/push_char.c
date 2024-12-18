/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 22:41:09 by sota              #+#    #+#             */
/*   Updated: 2024/12/09 02:19:21 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/std_string.h>

int	__push_ch(t_string *str, size_t size, unsigned char c)
{
	if (str->len + 1 < size)
		return (ft_str_push(str, c));
	str->len++;
	return (0);
}
