/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 02:00:19 by sota              #+#    #+#             */
/*   Updated: 2025/05/29 02:00:50 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_string.h>
#include <stdlib.h>

int	split_into_key_value(char *str, char **key, char **value)
{
	char	*equal;

	equal = ft_strchr(str, '=');
	if (equal == NULL)
	{
		*key = ft_strdup(str);
		*value = ft_strdup("");
	}
	else
	{
		*key = ft_strndup(str, equal - str);
		*value = ft_strdup(equal + 1);
	}
	if (*key == NULL || *value == NULL)
	{
		free(*key);
		free(*value);
		return (-1);
	}
	return (0);
}
