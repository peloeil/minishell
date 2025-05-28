/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 09:03:16 by marvin            #+#    #+#             */
/*   Updated: 2025/05/29 02:35:17 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <minishell/execute.h>
#include <libft/ft_stdio.h>
#include <libft/ft_string.h>
#include <stdlib.h>

int	count_argv(char **argv)
{
	int	count;

	count = 0;
	while (argv[count] != NULL)
		count++;
	return (count);
}

int	make_str(int is_double, t_string *str, const char *key, const char *value)
{
	int	status;

	status = 0;
	if (is_double == 0)
	{
		status |= ft_str_push_str(str, key);
		status |= ft_str_push_str(str, "=");
		status |= ft_str_push_str(str, value);
		status |= ft_str_push_str(str, "\n");
		return (status);
	}
	status |= ft_str_push_str(str, key);
	status |= ft_str_push_str(str, "=\"");
	status |= ft_str_push_str(str, value);
	status |= ft_str_push_str(str, "\"\n");
	return (status);
}

int	print_sorted_env(int fd, t_envp *envp)
{
	int	status;

	status = 0;
	sort_envp(&envp);
	while (envp != NULL)
	{
		if (envp->flag & FLAG_SPECIAL)
		{
			envp = envp->next;
			continue ;
		}
		if ((envp->flag & FLAG_ENV) && ft_strcmp(envp->key, "_") != 0)
			status = ft_dprintf(fd, "declare -x %s=\"%s\"\n", envp->key,
					envp->value);
		else if ((envp->flag & FLAG_EXPORT))
			status = ft_dprintf(fd, "declare -x %s\n", envp->key);
		envp = envp->next;
	}
	if (status == -1)
		return (STATUS_ERRORS);
	return (STATUS_SUCCESS);
}

void	swap_envp_nodes(t_envp *curr)
{
	char	*tmp_key;
	char	*tmp_value;
	int		tmp_i;

	tmp_key = curr->key;
	tmp_value = curr->value;
	tmp_i = curr->flag;
	curr->key = curr->next->key;
	curr->value = curr->next->value;
	curr->flag = curr->next->flag;
	curr->next->key = tmp_key;
	curr->next->value = tmp_value;
	curr->next->flag = tmp_i;
}

void	sort_envp(t_envp **head)
{
	int		sorted;
	t_envp	*curr;

	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		curr = *head;
		while (curr && curr->next)
		{
			if (ft_strcmp(curr->key, curr->next->key) > 0)
			{
				swap_envp_nodes(curr);
				sorted = 0;
			}
			curr = curr->next;
		}
	}
}
