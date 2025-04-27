/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/20 04:07:32 by yonuma            #+#    #+#             */
/*   Updated: 2025/04/21 11:18:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <stdlib.h>
#include <libft/ft_stdio.h>

int env(const char **envp)
{
    int    i;

    if (envp == NULL)
        return (EXIT_FAILURE);
    i = 0;
    while (envp[i] != NULL)
    {
        ft_printf("%s\n", envp[i]);
        i++;
    }
    return (EXIT_SUCCESS);
}
