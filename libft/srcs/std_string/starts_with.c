/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   starts_with.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 03:57:56 by sota              #+#    #+#             */
/*   Updated: 2024/12/03 04:18:10 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_string.h>
#include <libft/std_string.h>

int	ft_str_starts_with(const t_string *str, const char *prefix)
{
	size_t	len;

	if (prefix == NULL)
		return (0);
	len = ft_strlen(prefix);
	if (str->len < len)
		return (0);
	return (ft_strncmp(str->str, prefix, len) == 0);
}
