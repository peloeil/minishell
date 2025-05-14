/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 00:08:58 by sota              #+#    #+#             */
/*   Updated: 2025/05/15 01:17:09 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <minishell/execute.h>
#include <libft/ft_string.h>
#include <libft/ft_stdlib.h>
#include <stdlib.h>

static int	ms_envp_push(t_envp **ms_envp, char *node)
{
	t_envp	*new_node;
	size_t	key_len;

	new_node = (t_envp *)ft_calloc(1, sizeof(t_envp));
	if (new_node == NULL)
		return (-1);
	key_len = ft_strchr(node, '=') - node;
	new_node->key = ft_strndup(node, key_len);
	new_node->value = ft_strdup(node + key_len + 1);
	if (new_node->key == NULL || new_node->value == NULL)
	{
		free(new_node->key);
		free(new_node->value);
		free(new_node);
		return (-1);
	}
	new_node->exported = 1;
	new_node->next = *ms_envp;
	*ms_envp = new_node;
	return (0);
}

int	make_ms_envp(t_envp **ms_envp, char **envp)
{
	size_t	i;

	*ms_envp = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		if (ms_envp_push(ms_envp, envp[i]) == -1)
		{
			free_ms_envp(*ms_envp);
			return (-1);
		}
		i++;
	}
	if (ms_envp_push(ms_envp, "OLDPWD=") == -1
		|| ms_envp_push(ms_envp, "?=0") == -1)
	{
		free_ms_envp(*ms_envp);
		return (-1);
	}
	return (0);
}

void	free_ms_envp(t_envp *env)
{
	t_envp	*next;

	while (env != NULL)
	{
		next = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = next;
	}
}
