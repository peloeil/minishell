/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/06 11:56:10 by sota              #+#    #+#             */
/*   Updated: 2024/12/06 11:58:13 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/std_string.h>

int	ft_str_insert(t_string *str, size_t idx, char c)
{
	if (idx >= str->len)
		return (-1);
	str->str[idx] = c;
	return (0);
}
