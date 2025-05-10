/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:05:06 by marvin            #+#    #+#             */
/*   Updated: 2025/05/06 11:05:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <stdlib.h>
#include <libft/ft_string.h>

int unset(char **argv, t_envp **envp)
{
	int		i;
	t_envp	*current;
	t_envp	*prev;

	if (count_argv(argv) < 2)
		return (0);
	i = 1;
	while (argv[i] != NULL)
	{
		current = *envp;
		prev = NULL;
		while (current != NULL && ft_strcmp(current->key, argv[i]) != 0)
		{
			prev = current;
			current = current->next;
		}
		if (current != NULL)
		{
			if (prev != NULL)
				prev->next = current->next;
			else
				*envp = current->next;
			free(current->key);
			free(current->value);
			free(current);
		}
		i++;
	}
	return (0);
}
