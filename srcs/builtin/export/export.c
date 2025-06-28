/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonuma <yonuma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:39:15 by yonuma            #+#    #+#             */
/*   Updated: 2025/06/28 20:34:55 by yonuma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <minishell/execute.h>
#include <libft/ft_ctype.h>
#include <libft/ft_stdio.h>
#include <libft/ft_string.h>
#include <stdlib.h>

static int	is_valid_key(const char *key)
{
	size_t	i;

	if (!key || !key[0])
		return (0);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	register_env(t_envp **envp, char *str)
{
	int		flag;
	char	*key;
	char	*value;

	if (split_into_key_value(str, &key, &value) == -1)
		return (-1);
	flag = (FLAG_EXPORT | FLAG_ENV);
	if (value == NULL)
		flag = FLAG_EXPORT;
	free(value);
	if (!is_valid_key(key))
	{
		free(key);
		ft_dprintf(STDERR_FILENO,
			"minishell: export: `%s': not a valid identifier\n", str);
		return (-1);
	}
	return (update_ms_envp(envp, str, flag));
}

int	export(int fd, char **argv, t_envp **envp)
{
	int	i;

	if (argv[1] == NULL)
		return (print_sorted_env(fd, *envp));
	i = 1;
	while (argv[i])
	{
		if (register_env(envp, argv[i]) == -1)
			return (STATUS_ERRORS);
		i++;
	}
	return (STATUS_SUCCESS);
}
