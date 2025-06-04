/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 02:00:19 by sota              #+#    #+#             */
/*   Updated: 2025/06/05 00:22:28 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_string.h>
#include <stdlib.h>

int	split_into_key_value(char *str, char **key, char **value)
{
	char	*equal;
	size_t	key_len;
	size_t	value_len;

	equal = ft_strchr(str, '=');
	key_len = ft_strlen(str);
	value_len = 0;
	if (equal == str + key_len - 1)
		key_len--;
	else if (equal != NULL)
	{
		value_len = key_len - (equal - str) - 1;
		key_len = equal - str;
	}
	*key = ft_strndup(str, key_len);
	*value = NULL;
	if (value_len > 0)
		*value = ft_strndup(equal + 1, value_len);
	if (*key == NULL || (value_len > 0 && *value == NULL))
	{
		free(*key);
		free(*value);
		return (-1);
	}
	return (0);
}
