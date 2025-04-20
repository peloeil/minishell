/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonuma <yonuma@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-16 05:28:19 by yonuma            #+#    #+#             */
/*   Updated: 2025-04-16 05:28:19 by yonuma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <stdlib.h>
#include <libft/ft_stdio.h>
#include <libft/libft.h>

int echo(int argc, char *argv[])
{
    int n_option;
    int i;

    n_option = 0;
    i = 0;
    while (i < argc)
    {
        if (ft_strncmp(argv[i], "-n", 2) == 0)
            n_option = 1;
        else
        {
            ft_printf("%s", argv[i]);
            if (i < argc - 1)
                ft_printf(" ");
        }
        i ++;
    }
    if (n_option != 1)
        ft_printf("\n");
    return (0);
}
