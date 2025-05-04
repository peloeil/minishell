/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_variable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:00:46 by sota              #+#    #+#             */
/*   Updated: 2025/05/04 17:41:45 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <libft/ft_ctype.h>
#include <libft/ft_string.h>
#include <libft/std_string.h>
#include <stdlib.h>

static char	*read_variable_key(char *str, size_t index)
{
	t_string	key;
	char		c;

	if (ft_isdigit(str[++index]))
		return (NULL);
	if (ft_str_new(&key) == -1)
		return (NULL);
	while (1)
	{
		c = str[index++];
		if (c == '_' || ft_isalnum(c))
		{
			if (ft_str_push(&key, c) == -1)
				return (NULL);
		}
		else
			break ;
	}
	return (key.str);
}

static char	*read_variable_value(char *key, const t_envp *envp)
{
	char	*value;

	if (key == NULL)
		return (NULL);
	value = ft_getenv(key, envp);
	if (value == NULL)
		value = "";
	return (ft_strdup(value));
}

int	push_expanded_str(
				t_string *new,
				char *str,
				size_t *index,
				const t_envp *envp)
{
	char	*key;
	char	*value;

	key = read_variable_key(str, *index);
	if (key == NULL)
		return (-1);
	value = read_variable_value(key, envp);
	if (value == NULL)
	{
		free(key);
		return (-1);
	}
	if (ft_str_push_str(new, value) == -1)
	{
		free(key);
		free(value);
		return (-1);
	}
	*index += 1 + ft_strlen(key);
	free(key);
	free(value);
	return (0);
}
