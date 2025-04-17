/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonuma <yonuma@student.42.fr>              #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-04-16 09:39:15 by yonuma            #+#    #+#             */
/*   Updated: 2025-04-16 09:39:15 by yonuma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <stdlib.h>
#include <libft/ft_stdio.h>
#include <libft/ft_string.h>
#include <string.h>

void bubble_sort(char **array, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (strcmp(array[j], array[j + 1]) > 0)
            {
                char *temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}

int print_sorted_env(const char **envp)
{
    int i;
    i = 0;
    while (envp[i] != NULL)
        i++;
    char **sorted_env = malloc(sizeof(char *) * (i + 1));
    if (!sorted_env)
        return (-1);
    int j;
    j = 0;
    while (j < i)
    {
        sorted_env[j] = ft_strdup(envp[j]);
        j++;
    }
    sorted_env[i] = NULL;

    bubble_sort(sorted_env, i);

    i = 0;
    while (sorted_env[i + 1] != NULL)
    {
        ft_printf("declare -x %s\n", sorted_env[i]);
        free(sorted_env[i]);
        i++;
    }
    free(sorted_env);

    return (0);
}

int export(char *argv[], const char **envp)
{
    if (argv[1] == NULL)
    {
        print_sorted_env(envp);
        return (0);
    }
    return (1);
}
