/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 18:52:21 by sota              #+#    #+#             */
/*   Updated: 2024/12/05 03:46:52 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/std_string.h>

int	ft_str_push(t_string *str, char c)
{
	if (ft_str_reserve(str, 1) == -1)
		return (-1);
	str->str[str->len++] = c;
	str->str[str->len] = '\0';
	return (0);
}
