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

void    make_str(int is_double, t_string *str, const char *key, const char *value)
{
	if (is_double == 0)
	{
		ft_str_push_str(str, key);
		ft_str_push_str(str, "=");
		ft_str_push_str(str, value);
		ft_str_push_str(str, "\n");
		return ;
	}
    ft_str_push_str(str, key);
    ft_str_push_str(str, "=\"");
    ft_str_push_str(str, value);
    ft_str_push_str(str, "\"\n");
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
	t_envp	*curr;
	char	*tmp_key;
	char	*tmp_value;

	sorted = 0;
	while (!sorted)
	{
		sorted = 1;
		curr = *head;
    	while (curr && curr->next)
		{
			if (ft_strcmp(curr->key, curr->next->key) > 0)
            {
                tmp_key = curr->key;
                tmp_value = curr->value;
                curr->key = curr->next->key;
                curr->value = curr->next->value;
                curr->next->key = tmp_key;
                curr->next->value = tmp_value;
                sorted = 0;
            }
            curr = curr->next;
        }
    }
}
