/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 09:03:16 by marvin            #+#    #+#             */
/*   Updated: 2025/05/02 20:22:11 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <libft/std_string.h>
#include <libft/ft_string.h>
#include <stdlib.h>
#include <libft/ft_stdio.h>

void	add_double_quotes(int fd, t_string *str, const char *key,
	const char *value)
{
	ft_str_push_str(str, key);
	ft_str_push_str(str, "=\"");
	ft_str_push_str(str, value);
	ft_str_push_str(str, "\"\n");
	ft_dprintf(fd, "%s", str->str);
}

void	print_sorted_env(int fd, t_envp *envp)
{
	sort_envp(&envp);
	while (envp != NULL)
	{
		ft_dprintf(fd, "declare -x %s=\"%s\"\n", envp->key, envp->value);
		envp = envp->next;
	}
}

void	sort_envp(t_envp **head)
{
	int		sorted;
	t_envp	**curr;
	t_envp	*tmp;

	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		curr = head;
		while ((*curr) && (*curr)->next)
		{
			if (ft_strcmp((*curr)->key, (*curr)->next->key) > 0)
			{
				tmp = (*curr)->next;
				(*curr)->next = tmp->next;
				tmp->next = *curr;
				*curr = tmp;
				sorted = 0;
			}
			curr = &(*curr)->next;
		}
	}
}
