/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 01:00:41 by sota              #+#    #+#             */
/*   Updated: 2025/05/29 01:13:28 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <libft/ft_stdlib.h>
#include <libft/ft_string.h>
#include <stdlib.h>

static int	split_into_key_value(char *str, char **key, char **value)
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

int	push_to_ms_envp(t_envp **ms_envp, char *str, int flag)
{
	t_envp	*node;

	node = (t_envp *)ft_calloc(1, sizeof(t_envp));
	if (node == NULL)
		return (-1);
	if (split_into_key_value(str, &node->key, &node->value) == -1)
	{
		free(node->key);
		free(node->value);
		free(node);
		return (-1);
	}
	node->flag = flag;
	node->next = *ms_envp;
	*ms_envp = node;
	return (0);
}
