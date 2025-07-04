/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonuma <yonuma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 01:00:41 by sota              #+#    #+#             */
/*   Updated: 2025/07/04 20:10:29 by yonuma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_stdio.h>
#include <libft/ft_stdlib.h>
#include <minishell/minishell.h>
#include <stdlib.h>

static int	push_to_ms_envp(t_envp **ms_envp, const char *str, int flag)
{
	t_envp	*node;

	node = (t_envp *)ft_calloc(1, sizeof(t_envp));
	if (node == NULL)
		return (-1);
	node->flag = flag;
	if (split_into_key_value(str, &node->key, &node->value) == -1)
	{
		free(node->key);
		free(node->value);
		free(node);
		return (-1);
	}
	node->next = *ms_envp;
	*ms_envp = node;
	return (0);
}

int	update_ms_envp(t_envp **envp, const char *str, int flag)
{
	char	*key;
	char	*value;
	t_envp	*old;

	if (split_into_key_value(str, &key, &value) == -1)
		return (-1);
	if (*envp == NULL)
	{
		free(key);
		free(value);
		return (push_to_ms_envp(envp, str, flag));
	}
	old = search_key(key, *envp);
	free(key);
	if (old == NULL)
	{
		free(value);
		return (push_to_ms_envp(envp, str, flag));
	}
	free(old->value);
	old->value = value;
	old->flag = flag;
	return (0);
}
