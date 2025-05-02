/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 00:08:58 by sota              #+#    #+#             */
/*   Updated: 2025/05/03 00:25:37 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <libft/ft_string.h>
#include <stdlib.h>

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
		env->exported = 1;
		env->next = next;
		next = env;
		i++;
	}
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
