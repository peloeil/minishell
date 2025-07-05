/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonuma <yonuma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:39:15 by yonuma            #+#    #+#             */
/*   Updated: 2025/06/29 09:29:03 by sota             ###   ########.fr       */
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

static int	export_oldpwd(t_envp **envp)
{
	char	*str;
	int		status;

	if (ft_asprintf(&str, "OLDPWD=%s", ft_getenv("OLDPWD", *envp)) == -1)
		return (-1);
	status = (update_ms_envp(envp, str, FLAG_EXPORT | FLAG_ENV) == -1);
	free(str);
	return (status);
}

static int	export_pwd(t_envp **envp)
{
	char	*str;

	if (ft_asprintf(&str, "PWD=%s", ft_getenv("!PWD", *envp)) == -1)
		return (-1);
	if (register_env(envp, str) == -1)
	{
		free(str);
		return (-1);
	}
	free(str);
	return (0);
}

int	register_env(t_envp **envp, char *str)
{
	int		flag;
	char	*key;
	char	*value;

	if (ft_strcmp(str, "PWD") == 0)
		return (export_pwd(envp));
	if (ft_strcmp(str, "OLDPWD") == 0)
		return (export_oldpwd(envp));
	if (search_key(str, *envp) != NULL)
		return (update_ms_envp(envp, str, FLAG_EXPORT));
	if (split_into_key_value(str, &key, &value) == -1)
		return (-1);
	flag = (FLAG_EXPORT | FLAG_ENV);
	if (value == NULL && ft_strchr(str, '=') == NULL)
		flag = FLAG_EXPORT;
	free(value);
	if (!is_valid_key(key))
	{
		free(key);
		ft_dprintf(STDERR_FILENO,
			"minishell: export: `%s': not a valid identifier\n", str);
		return (-1);
	}
	free(key);
	return (update_ms_envp(envp, str, flag));
}

int	export(int fd, char **argv, t_envp **envp)
{
	int	i;
	int	status;

	if (argv[1] == NULL)
		return (print_sorted_env(fd, *envp));
	i = 1;
	status = STATUS_SUCCESS;
	while (argv[i])
	{
		status |= (register_env(envp, argv[i]) == -1);
		i++;
	}
	return (status);
}
