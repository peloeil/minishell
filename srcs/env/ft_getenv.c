/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 22:18:58 by sota              #+#    #+#             */
/*   Updated: 2025/05/03 00:55:12 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <libft/ft_string.h>

char	*ft_getenv(const char *key, const t_envp *envp)
{
	char	*value;

	value = NULL;
	while (envp != NULL)
	{
		if (ft_strcmp(key, envp->key) == 0)
		{
			value = envp->value;
			break ;
		}
		envp = envp->next;
	}
	return (value);
}
