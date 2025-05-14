/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 18:08:24 by marvin            #+#    #+#             */
/*   Updated: 2025/05/14 18:08:24 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_stdio.h>
#include <libft/ft_string.h>
#include <minishell/minishell.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	add_envp_with_flag(char *key, char *value, t_envp *envp, int flags)
{
	t_envp	*current;
	t_envp	*new_node;

	current = envp;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			current->exported = flags;
			return ;
		}
		if (current->next == NULL)
			break ;
		current = current->next;
	}
	new_node = create_new_node(ft_strdup(key), ft_strdup(value), flags);
	if (!new_node)
	{
		free(key);
		free(value);
		return ;
	}
	current->next = new_node;
}

void	update_env_value(const char *key, const char *value, t_envp *envp)
{
	t_envp	*current;

	current = envp;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
}

int	get_env_flags(const char *key, t_envp *envp)
{
	t_envp	*current;

	current = envp;
	while (current != NULL)
	{
		if (ft_strcmp(current->key, key) == 0)
			return (current->exported);
		current = current->next;
	}
	return (-1);
}
