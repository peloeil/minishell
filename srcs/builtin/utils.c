/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 09:03:16 by marvin            #+#    #+#             */
/*   Updated: 2025/05/03 11:28:20 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <libft/std_string.h>
#include <libft/ft_string.h>
#include <stdlib.h>
#include <libft/ft_stdio.h>

int	count_argv(char **argv)
{
	int	count;

	count = 0;
	while (argv[count] != NULL)
		count++;
	return (count);
}

int	make_str(int is_double, t_string *str,
	const char *key, const char *value)
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
		if (envp->exported & (FLAG_UNSET | FLAG_SPECIAL) || envp->exported == 0)
		{
			envp = envp->next;
			continue ;
		}
		else if ((envp->exported & FLAG_EXPORT)
			&& ft_strcmp(envp->key, "_") != 0)
			status = ft_dprintf(fd, "declare -x %s=\"%s\"\n", envp->key, envp->value);
		else if ((envp->exported & FLAG_VALUE))
			status = ft_dprintf(fd, "declare -x %s\n", envp->key);
		envp = envp->next;
	}
	if (status == -1)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}

void	swap_envp_nodes(t_envp *curr)
{
	char	*tmp_key;
	char	*tmp_value;
	int		tmp_i;

	tmp_key = curr->key;
	tmp_value = curr->value;
	tmp_i = curr->exported;
	curr->key = curr->next->key;
	curr->value = curr->next->value;
	curr->exported = curr->next->exported;
	curr->next->key = tmp_key;
	curr->next->value = tmp_value;
	curr->next->exported = tmp_i;
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
			// ft_printf("test:  %s=%s\n", curr->key, curr->value);
			if (ft_strcmp(curr->key, curr->next->key) > 0)
			{
				swap_envp_nodes(curr);
				sorted = 0;
			}
			curr = curr->next;
		}
	}
}

// sort 時には存在しているPATHがソートすると非表示になる