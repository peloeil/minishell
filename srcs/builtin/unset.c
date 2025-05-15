/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:05:06 by marvin            #+#    #+#             */
/*   Updated: 2025/05/15 04:02:22 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_string.h>
#include <minishell/minishell.h>
#include <stdlib.h>

static void	remove_env_key(t_envp **envp, const char *key)
{
	t_envp	*current;
	t_envp	*prev;
	t_envp	*next_node;

	current = *envp;
	prev = NULL;
	while (current != NULL && ft_strcmp(current->key, key) != 0)
	{
		prev = current;
		current = current->next;
	}
	if (current != NULL)
	{
		next_node = current->next;
		if (prev != NULL)
			prev->next = next_node;
		else
			*envp = next_node;
		free(current->key);
		free(current->value);
		free(current);
	}
}

int	unset(int fd, char **argv, t_envp **envp)
{
	int	i;

	(void)fd;
	if (count_argv(argv) < 2)
		return (0);
	i = 1;
	while (argv[i] != NULL)
	{
		remove_env_key(envp, argv[i]);
		i++;
	}
	return (0);
}
