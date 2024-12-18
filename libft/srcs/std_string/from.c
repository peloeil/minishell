/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   from.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 19:07:45 by sota              #+#    #+#             */
/*   Updated: 2024/12/03 02:14:13 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_string.h>
#include <libft/std_string.h>

int	ft_str_from(t_string *str, const char *s)
{
	size_t	len;

	if (s == NULL)
		return (-1);
	len = ft_strlen(s);
	if (ft_str_with_capacity(str, len) == -1)
		return (-1);
	ft_strlcpy(str->str, s, len + 1);
	str->len = len;
	return (0);
}
