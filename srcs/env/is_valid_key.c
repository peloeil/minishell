/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid_key.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonuma <yonuma@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/24 07:05:51 by yonuma            #+#    #+#             */
/*   Updated: 2025/05/29 02:42:58 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_ctype.h>
#include <stddef.h>

int	is_valid_key(const char *key)
{
	size_t	i;

	if (!key || !key[0])
		return (0);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
