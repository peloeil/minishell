/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:39:15 by yonuma            #+#    #+#             */
/*   Updated: 2025/05/10 19:33:10 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_stdio.h>
#include <libft/ft_string.h>
#include <minishell/minishell.h>
#include <stdlib.h>
#include <string.h>

t_envp	*create_new_node(char *key, char *value, int exported)
{
	t_envp	*new_node;

	new_node = malloc(sizeof(t_envp));
	if (!new_node)
		return (NULL);
	new_node->key = key;
	if (value != NULL)
		new_node->value = value;
	else
		new_node->value = ft_strdup("");
	new_node->exported = exported;
	new_node->next = NULL;
	return (new_node);
}

void	register_env_with_value(t_envp *envp, char *key, char *value)
{
	t_envp	*new_node;

	while (envp != NULL)
	{
		if (ft_strcmp(envp->key, key) == 0)
		{
			free(envp->value);
			envp->value = value;
			free(key);
			return ;
		}
		if (envp->next == NULL)
			break ;
		envp = envp->next;
	}
	new_node = create_new_node(key, value, 1);
	if (!new_node)
	{
		free(key);
		free(value);
		return ;
	}
	envp->next = new_node;
}

void	register_env_without_value(t_envp *envp, char *key)
{
	t_envp	*curr;
	t_envp	*new_node;

	curr = envp;
	while (curr != NULL)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (curr->exported & FLAG_UNSET)
			{
				curr->exported &= ~FLAG_UNSET;
				curr->exported |= FLAG_EXPORT;
			}
			free(key);
			return ;
		}
		if (curr->next == NULL)
			break ;
		curr = curr->next;
	}
	new_node = create_new_node(key, NULL, FLAG_EXPORT);
	if (!new_node)
	{
		free(key);
		return ;
	}
	curr->next = new_node;
}

void	register_env(t_envp *envp, char *str)
{
	char	*key;
	char	*value;
	char	*delimiter_pos;

	delimiter_pos = ft_strchr(str, '=');
	if (delimiter_pos == NULL)
	{
		key = ft_strdup(str);
		if (!key)
			return ;
		register_env_without_value(envp, key);
		return ;
	}
	key = ft_substr(str, 0, delimiter_pos - str);
	value = ft_strdup(delimiter_pos + 1);
	if (!key || !value)
	{
		free(key);
		free(value);
		return ;
	}
	register_env_with_value(envp, key, value);
}

int	export(int fd, char *argv[], t_envp *envp)
{
	if (argv[1] == NULL)
		print_sorted_env(fd, envp);
	else
		register_env(envp, argv[1]);
	return (0);
}
