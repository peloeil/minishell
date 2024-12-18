/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ends_with.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 04:06:58 by sota              #+#    #+#             */
/*   Updated: 2024/12/03 04:18:04 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_string.h>
#include <libft/std_string.h>

int	ft_str_ends_with(const t_string *str, const char *suffix)
{
	size_t	len;

	if (suffix == NULL)
		return (0);
	len = ft_strlen(suffix);
	if (str->len < len)
		return (0);
	return (ft_strncmp(str->str + str->len - len, suffix, len) == 0);
}
