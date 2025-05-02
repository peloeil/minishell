/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 22:18:58 by sota              #+#    #+#             */
/*   Updated: 2025/05/02 11:51:36 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_string.h>
#include <minishell/minishell.h>

char	*ft_getenv(const char *key, t_minishell_envp *minishell_envp)
{
    size_t	key_len;

    key_len = ft_strlen(key);
    while (minishell_envp != NULL)
    {
        if (ft_strncmp(key, minishell_envp->key, key_len) == 0
			&& minishell_envp->key[key_len] == '\0')
            return (minishell_envp->value);
        minishell_envp = minishell_envp->next;
    }
    return (NULL);
}
