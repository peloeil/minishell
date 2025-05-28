/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ms_envp.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 00:57:35 by sota              #+#    #+#             */
/*   Updated: 2025/05/29 01:11:44 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <libft/ft_string.h>
#include <stdlib.h>

static int	ms_envp_push_pwd(t_envp **ms_envp, char *node)
{
	t_envp	*new_node;
	size_t	key_len;

	if (ft_getenv("!PWD", *ms_envp) != NULL)
		return (0);
	new_node = (t_envp *)ft_calloc(1, sizeof(t_envp));
	if (new_node == NULL)
		return (-1);
	key_len = 4;
	new_node->key = ft_strndup(node, key_len);
	new_node->value = getcwd(NULL, 0);
	if (new_node->key == NULL)
	{
		free(new_node->key);
		free(new_node->value);
		free(new_node);
		return (-1);
	}
	new_node->flag = 0;
	new_node->next = *ms_envp;
	*ms_envp = new_node;
	return (0);
}

static int	ms_envp_push_oldpwd(t_envp **ms_envp, char *node)
{
	t_envp	*new_node;
	size_t	key_len;

	if (ft_getenv("OLDPWD", *ms_envp) != NULL)
		return (0);
	new_node = (t_envp *)ft_calloc(1, sizeof(t_envp));
	if (new_node == NULL)
		return (-1);
	key_len = 6;
	new_node->key = ft_strndup(node, key_len);
	new_node->value = NULL;
	if (new_node->key == NULL)
	{
		free(new_node->key);
		free(new_node->value);
		free(new_node);
		return (-1);
	}
	new_node->flag = FLAG_VALUE;
	new_node->next = *ms_envp;
	*ms_envp = new_node;
	return (0);
}



int	init_ms_envp(t_envp **ms_envp, char **envp)
{
	size_t	i;

	*ms_envp = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		if (push_to_ms_envp(ms_envp, envp[i], FLAG_EXPORT | FLAG_ENV) == -1)
		{
			free_ms_envp(*ms_envp);
			return (-1);
		}
		i++;
	}
	if (init_specials(ms_envp) == -1)
	{
		free_ms_envp(*ms_envp);
		return (-1);
	}
	return (0);
}
	// if (ms_envp_push_oldpwd(ms_envp, "OLDPWD") == -1
	// 	|| ms_envp_push_pwd(ms_envp, "!PWD") == -1 || update_exit_status(0,
	// 		*ms_envp) == -1)
	// {
	// 	free_ms_envp(*ms_envp);
	// 	return (-1);
	// }
