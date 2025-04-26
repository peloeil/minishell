/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:39:15 by yonuma            #+#    #+#             */
/*   Updated: 2025/04/26 18:37:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <stdlib.h>
#include <libft/ft_stdio.h>
#include <libft/ft_string.h>
#include <string.h>

void bubble_sort(char **array, int size)
{
    int     i = 0;
    char    *temp;

    while (i < size - 1)
    {
        int j = 0;
        while (j < size - i - 1)
        {
            if (ft_strcmp(array[j], array[j + 1]) > 0)
            {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
            j++;
        }
        i++;
    }
}

int add_double_quote(t_minishell_envp *envp, char **envp_copy)
{
    char *temp;
    int i;

    i = 0;
    while (envp != NULL && envp->exported == 1)
    {
        envp_copy[i] = ft_strjoin(envp->key, "=");
        temp = envp_copy[i];
        envp_copy[i] = ft_strjoin(envp_copy[i], "\"");
        free(temp);
        temp = envp_copy[i];
        envp_copy[i] = ft_strjoin(envp_copy[i], envp->value);
        free(temp);
        temp = envp_copy[i];
        envp_copy[i] = ft_strjoin(envp_copy[i], "\"");
        free(temp);
        envp = envp->next;
        i++;
    }
    return (i);
}

int print_sorted_env(t_minishell_envp *envp)
{
    char **envp_copy;
    int i;

    envp_copy = malloc(sizeof(char *) * 1000);
    if (!envp_copy)
        return (-1);
    i = add_double_quote(envp, envp_copy);
    envp_copy[i] = NULL;
    bubble_sort(envp_copy, i);
    i = 0;
    while (envp_copy[i] != NULL)
    {
        if (envp_copy[i][0] != '_')
        {
            ft_printf("declare -x %s\n", envp_copy[i]);
            free(envp_copy[i]);
        }
        i++;
    }
    free(envp_copy);
    return (0);
}

void	register_env_with_value(t_minishell_envp *envp, char *key, char *value)
{
	while (envp != NULL)
	{
		if (ft_strcmp(envp->key, key) == 0)
		{
			free(envp->value);
			envp->value = value;
			free(key);
			return ;
		}
		if (envp->next == NULL)
			break;
		envp = envp->next;
	}
	t_minishell_envp *new_node = malloc(sizeof(t_minishell_envp));
	if (!new_node)
	{
		free(key);
		free(value);
		return ;
	}
	new_node->key = key;
	new_node->value = value;
	new_node->exported = 1;
	new_node->next = NULL;
	envp->next = new_node;
}

void	register_env_without_value(t_minishell_envp *envp, char *key)
{
	while (envp->next != NULL)
		envp = envp->next;
	t_minishell_envp *new_node = malloc(sizeof(t_minishell_envp));
	if (!new_node)
	{
		free(key);
		return ;
	}
	new_node->key = key;
	new_node->value = ft_strdup("");
	new_node->exported = 1;
	new_node->next = NULL;
	envp->next = new_node;
}

void	register_env(t_minishell_envp *envp, char *str)
{
	char *key;
	char *value;
	char *delimiter_pos;

	delimiter_pos = ft_strchr(str, '=');
	if (delimiter_pos == NULL)
	{
		key = ft_strdup(str);
		if (!key)
			return ;
		register_env_without_value(envp, key);
		return ;
	}
	key = ft_substr(str, 0, delimiter_pos - str);
	value = ft_strdup(delimiter_pos + 1);
	if (!key || !value)
	{
		free(key);
		free(value);
		return ;
	}
	register_env_with_value(envp, key, value);
}

int export(char *argv[], t_minishell_envp *envp)
{
    if (argv[1] == NULL)
        print_sorted_env(envp);
    else
        register_env(envp, argv[1]);
    return (0);
}
