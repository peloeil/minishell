/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 02:47:43 by sota              #+#    #+#             */
/*   Updated: 2025/06/05 01:16:47 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <minishell/execute.h>
#include <libft/std_string.h>
#include <libft/ft_string.h>
#include <libft/ft_stdio.h>
#include <stdlib.h>

static void	swap_envp_nodes(t_envp *curr)
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

static void	sort_envp(t_envp **head)
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

static int	print_export_key_value(int fd, const char *key, const char *value)
{
	t_string	str;
	size_t		i;

	if (ft_str_from(&str, "declare -x ") == -1
		|| ft_str_push_str(&str, key) == -1
		|| ft_str_push_str(&str, "=\"") == -1)
		return (-1);
	i = 0;
	while (value[i] != '\0')
	{
		if (value[i] != '"' && ft_str_push(&str, value[i]) == -1)
			return (-1);
		if (value[i] == '"' && ft_str_push_str(&str, "\\\"") == -1)
			return (-1);
		i++;
	}
	if (ft_str_push_str(&str, "\"\n") == -1)
		return (-1);
	if (ft_dprintf(fd, "%s", str.str) == -1)
	{
		free(str.str);
		return (-1);
	}
	free(str.str);
	return (0);
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
		if ((envp->flag & FLAG_EXPORT) && (envp->flag & FLAG_ENV)
			&& ft_strcmp(envp->key, "_") != 0)
			status |= (print_export_key_value(fd,
						envp->key, envp->value) == -1);
		else if ((envp->flag & FLAG_EXPORT) && ft_strcmp(envp->key, "_") != 0)
			status |= (ft_dprintf(fd, "declare -x %s\n", envp->key) == -1);
		envp = envp->next;
	}
	if (status == -1)
		return (STATUS_ERRORS);
	return (STATUS_SUCCESS);
}
