/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_str.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 22:33:54 by sota              #+#    #+#             */
/*   Updated: 2024/12/05 03:43:21 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_string.h>
#include <libft/std_string.h>

int	ft_str_push_str(t_string *str, const char *s)
{
	size_t	len;

	if (s == NULL)
		return (-1);
	len = ft_strlen(s);
	if (ft_str_reserve(str, len) == -1)
		return (-1);
	ft_memcpy(str->str + str->len, s, len + 1);
	str->len += len;
	return (0);
}
