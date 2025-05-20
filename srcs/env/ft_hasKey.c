/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hasKey.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonuma <yonuma@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-20 01:22:40 by yonuma            #+#    #+#             */
/*   Updated: 2025-05-20 01:22:40 by yonuma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <libft/ft_string.h>

int	ft_hasKey(char *key, t_envp *envp)
{
	int	hasKey;

	hasKey = 0;
	while (envp)
	{
		if (ft_strcmp(key, envp->key) == 0)
		{
			hasKey = 1;
			break;
		}
		envp = envp->next;
	}
	return (hasKey);
}