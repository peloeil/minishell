/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:39:15 by yonuma            #+#    #+#             */
/*   Updated: 2025/05/15 03:56:23 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_stdio.h>
#include <libft/ft_string.h>
#include <minishell/minishell.h>
#include <stdlib.h>

int	register_env_with_value(t_envp *envp, char *key, char *value)
{
	t_envp	*new_node;

	while (envp->next && ft_strcmp(envp->key, key) != 0)
		envp = envp->next;
	if (ft_strcmp(envp->key, key) == 0)
	{
		free(envp->value);
		envp->value = value;
		envp->exported = FLAG_EXPORT;
		free(key);
		return (EXIT_SUCCESS);
	}
	if (ft_strcmp(key, "?") == 0)
		new_node = create_new_node(key, value, FLAG_SPECIAL);
	else
		new_node = create_new_node(key, value, FLAG_EXPORT);
	if (!new_node)
	{
		free(key);
		free(value);
		return (EXIT_FAILURE);
	}
	envp->next = new_node;
	return (EXIT_SUCCESS);
}

int	register_env_without_value(t_envp *envp, char *key)
{
	t_envp	*curr;
	t_envp	*new_node;

	curr = envp;
	while (curr != NULL)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (curr->exported & FLAG_UNSET)
				curr->exported = (curr->exported & ~FLAG_UNSET) | FLAG_EXPORT;
			free(key);
			return (EXIT_SUCCESS);
		}
		if (curr->next == NULL)
			break ;
		curr = curr->next;
	}
	new_node = create_new_node(key, NULL, FLAG_VALUE);
	if (!new_node)
	{
		free(key);
		return (EXIT_FAILURE);
	}
	curr->next = new_node;
	return (EXIT_SUCCESS);
}

int	null_delimiter_pos(t_envp *envp, char *key)
{
	if (!key)
		return (EXIT_FAILURE);
	if (!is_valid_env_key(key))
	{
		ft_dprintf(STDERR_FILENO, "minishell: export: `%s': %s\n", key,
			NO_VALID);
		return (free(key), EXIT_FAILURE);
	}
	return (register_env_without_value(envp, key));
}

int	register_env(t_envp *envp, char *str)
{
	char	*key;
	char	*value;
	char	*delimiter_pos;

	delimiter_pos = ft_strchr(str, '=');
	if (delimiter_pos == NULL)
	{
		key = ft_strdup(str);
		return (null_delimiter_pos(envp, key));
	}
	key = ft_substr(str, 0, delimiter_pos - str);
	value = ft_strdup(delimiter_pos + 1);
	if (!key || !value)
		return (free(key), free(value), EXIT_FAILURE);
	if (!is_valid_env_key(key))
	{
		ft_dprintf(STDERR_FILENO, "minishell: export: `%s=%s': %s\n", key,
			value, NO_VALID);
		return (free(key), free(value), EXIT_FAILURE);
	}
	return (register_env_with_value(envp, key, value));
}

int	export(int fd, char **argv, t_envp **envp)
{
	int	i;
	int	status;

	status = 0;
	if (argv[1] == NULL)
		return (print_sorted_env(fd, *envp));
	i = 1;
	while (argv[i])
	{
		status = register_env(*envp, argv[i]);
		if (status == EXIT_FAILURE)
			return (EXIT_FAILURE);
		i++;
	}
	return (status);
}
