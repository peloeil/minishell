/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_value.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 22:18:58 by sota              #+#    #+#             */
/*   Updated: 2025/03/12 22:12:14 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_string.h>

char	*find_value(const char **envp, const char *key)
{
	size_t	i;
	size_t	key_len;
	char	*value;

	key_len = ft_strlen(key);
	i = 0;
	value = NULL;
	while (value == NULL && envp[i] != NULL)
	{
		if (ft_strncmp(key, envp[i], key_len) == 0 && envp[i][key_len] == '=')
			value = (char *)envp[i] + key_len + 1;
		i++;
	}
	return (value);
}
