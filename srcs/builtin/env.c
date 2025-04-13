/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonuma <yonuma@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-12 08:35:57 by yonuma            #+#    #+#             */
/*   Updated: 2025-04-12 08:35:57 by yonuma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <stdlib.h>
#include <libft/ft_stdio.h>

int env(char **argv, const char **envp)
{
    int	i;

    (void)argv;
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
