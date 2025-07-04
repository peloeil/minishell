/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonuma <yonuma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 09:39:15 by yonuma            #+#    #+#             */
/*   Updated: 2025/07/04 21:01:39 by yonuma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_ctype.h>
#include <libft/ft_stdio.h>
#include <libft/ft_string.h>
#include <minishell/execute.h>
#include <minishell/minishell.h>
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

static int	make_env_str(char **result, const char *key, const char *value)
{
	size_t	len;

	len = ft_strlen(key) + 1 + ft_strlen(value) + 1;
	*result = (char *)malloc(len);
	if (*result == NULL)
		return (-1);
	ft_snprintf(*result, len, "%s=%s", key, value);
	return (0);
}

static int	handle_env_update(t_envp **envp, char *key, char *value, int flag)
{
	t_envp	*exist;
	char	*result;
	int		ret;

	if (value == NULL)
	{
		exist = search_key(key, *envp);
		if (exist && exist->value)
		{
			if (make_env_str(&result, key, exist->value) == -1)
				return (free(key), -1);
			ret = update_ms_envp(envp, result, flag | FLAG_ENV);
			free(result);
			return (free(key), ret);
		}
		ret = update_ms_envp(envp, key, flag);
		return (free(key), ret);
	}
	if (make_env_str(&result, key, value) == -1)
		return (free(key), free(value), -1);
	ret = update_ms_envp(envp, result, flag);
	free(result);
	return (ret);
}

int	register_env(t_envp **envp, char *str)
{
	int		flag;
	int		result;
	char	*key;
	char	*value;

	if (split_into_key_value(str, &key, &value) == -1)
		return (-1);
	flag = (FLAG_EXPORT | FLAG_ENV);
	if (value == NULL)
		flag = FLAG_EXPORT;
	if (!is_valid_key(key))
	{
		ft_dprintf(STDERR_FILENO,
			"minishell: export: \
`%s': not a valid identifier\n", str);
		return (free(key), free(value), -1);
	}
	result = handle_env_update(envp, key, value, flag);
	return (free(key), free(value), result);
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
