/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 22:18:58 by sota              #+#    #+#             */
/*   Updated: 2025/05/29 02:29:58 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>

char	*ft_getenv(const char *key, const t_envp *envp)
{
	t_envp	*node;

	node = search_key(key, (t_envp *)envp);
	if (node == NULL)
		return (NULL);
	return (node->value);
}
