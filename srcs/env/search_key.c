/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_key.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 01:55:53 by sota              #+#    #+#             */
/*   Updated: 2025/05/29 02:29:23 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <libft/ft_string.h>

t_envp	*search_key(const char *key, t_envp *envp)
{
	t_envp	*cur;

	cur = envp;
	while (cur != NULL)
	{
		if (ft_strcmp(cur->key, key) == 0)
			return (cur);
		cur = cur->next;
	}
	return (NULL);
}
