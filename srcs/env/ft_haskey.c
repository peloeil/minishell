/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_haskey.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonuma <yonuma@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-05-20 01:22:40 by yonuma            #+#    #+#             */
/*   Updated: 2025-05-20 01:22:40 by yonuma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_string.h>
#include <minishell/minishell.h>

int	ft_haskey(char *key, t_envp *envp)
{
	int haskey;

	haskey = 0;
	while (envp)
	{
		if (ft_strcmp(key, envp->key) == 0)
		{
			haskey = 1;
			break ;
		}
		envp = envp->next;
	}
	return (haskey);
}