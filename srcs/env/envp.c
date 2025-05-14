/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 00:08:58 by sota              #+#    #+#             */
/*   Updated: 2025/05/06 14:36:19 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <libft/ft_string.h>
#include <stdlib.h>

t_envp	*make_oldpwd(t_envp *env, t_envp *next)
{
	env = (t_envp *)malloc(sizeof(t_envp));
	env->key = ft_strdup("OLDPWD");
	env->value = ft_strdup("");
	env->exported = 0;
	env->next = next;
	next = env;
	return (env);
}

t_envp	*make_ms_envp(char **envp)
{
	size_t	i;
	size_t	key_len;
	t_envp	*env;
	t_envp	*next;

	env = NULL;
	next = NULL;
	i = 0;
	while (envp[i] != NULL)
	{
		env = (t_envp *)malloc(sizeof(t_envp));
		key_len = ft_strchr(envp[i], '=') - envp[i];
		env->key = ft_strndup(envp[i], key_len);
		env->value = ft_strdup(envp[i] + key_len + 1);
		env->exported = FLAG_EXPORT;
		env->next = next;
		next = env;
		i++;
	}
	env = make_oldpwd(env, next);
	return (env);
}

void	free_ms_envp(t_envp *env)
{
	t_envp	*next;

	while (env != NULL)
	{
		next = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = next;
	}
}
