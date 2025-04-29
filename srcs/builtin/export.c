/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:39:15 by yonuma            #+#    #+#             */
/*   Updated: 2025/04/30 00:25:13 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <stdlib.h>
#include <libft/ft_stdio.h>
#include <libft/ft_string.h>
#include <string.h>

void	sort_envp(t_minishell_envp **head)
{
	int					sorted;
	t_minishell_envp	**curr;

	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		curr = head;
		while ((*curr) && (*curr)->next)
		{
			if (ft_strcmp((*curr)->key, (*curr)->next->key) > 0)
			{
				t_minishell_envp *tmp = (*curr)->next;
				(*curr)->next = tmp->next;
				tmp->next = *curr;
				*curr = tmp;
				sorted = 0;
			}
			curr = &(*curr)->next;
		}
	}
}

void	print_sorted_env(int fd, t_minishell_envp *envp)
{
	sort_envp(&envp);
	while (envp != NULL)
	{
		if (envp->key[0] != '_')
			ft_dprintf(fd, "declare -x %s=\"%s\"\n", envp->key, envp->value);
		envp = envp->next;
	}
}

void	register_env_with_value(t_minishell_envp *envp, char *key, char *value)
{
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
			break;
		envp = envp->next;
	}
	t_minishell_envp *new_node = malloc(sizeof(t_minishell_envp));
	if (!new_node)
	{
		free(key);
		free(value);
		return ;
	}
	new_node->key = key;
	new_node->value = value;
	new_node->exported = 1;
	new_node->next = NULL;
	envp->next = new_node;
}

void	register_env_without_value(t_minishell_envp *envp, char *key)
{
	while (envp->next != NULL)
		envp = envp->next;
	t_minishell_envp *new_node = malloc(sizeof(t_minishell_envp));
	if (!new_node)
	{
		free(key);
		return ;
	}
	new_node->key = key;
	new_node->value = ft_strdup("");
	new_node->exported = 1;
	new_node->next = NULL;
	envp->next = new_node;
}

void	register_env(t_minishell_envp *envp, char *str)
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

int	export(int fd, char *argv[], t_minishell_envp *envp)
{
	if (argv[1] == NULL)
		print_sorted_env(fd, envp);
	else
		register_env(envp, argv[1]);
	return (0);
}
