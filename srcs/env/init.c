/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yonuma <yonuma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/29 00:57:35 by sota              #+#    #+#             */
/*   Updated: 2025/06/28 20:35:42 by yonuma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <libft/ft_stdio.h>
#include <libft/ft_string.h>
#include <libft/ft_stdlib.h>
#include <stdlib.h>
#include <unistd.h>

static int	update_pwd(t_envp **envp)
{
	char	*pwd_value;
	char	*str;

	pwd_value = getcwd(NULL, 0);
	if (pwd_value == NULL)
		return (-1);
	if (ft_asprintf(&str, "!PWD=%s", pwd_value) == -1)
	{
		free(pwd_value);
		return (-1);
	}
	if (update_ms_envp(envp, str, FLAG_SPECIAL) == -1
		|| update_ms_envp(envp, str + 1, FLAG_EXPORT | FLAG_ENV) == -1)
	{
		free(pwd_value);
		free(str);
		return (-1);
	}
	return (0);
}

static int	init_special_vars(t_envp **ms_envp)
{
	if (update_pwd(ms_envp) == -1
		|| update_ms_envp(ms_envp, "OLDPWD=", FLAG_EXPORT) == -1
		|| update_ms_envp(ms_envp, "?=0", FLAG_SPECIAL) == -1)
		return (-1);
	return (0);
}

int	init_ms_envp(t_envp **ms_envp, char **envp)
{
	size_t	i;

	*ms_envp = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		if (register_env(ms_envp, envp[i]) == -1)
		{
			free_ms_envp(*ms_envp);
			return (-1);
		}
		i++;
	}
	if (init_special_vars(ms_envp) == -1)
	{
		free_ms_envp(*ms_envp);
		return (-1);
	}
	return (0);
}
