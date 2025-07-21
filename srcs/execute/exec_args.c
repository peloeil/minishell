/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:11:31 by sota              #+#    #+#             */
/*   Updated: 2025/05/10 16:18:55 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <minishell/parser.h>
#include <libft/ft_string.h>
#include <libft/ft_stdio.h>
#include <libft/ft_ctype.h>
#include <stdlib.h>

int	make_argv(char ***argv, t_arg_list *args)
{
	size_t		i;
	t_arg_list	*cur;

	*argv = (char **)malloc(sizeof(char *) * (ft_list_size(args) + 1));
	if (*argv == NULL)
		return (-1);
	i = 0;
	cur = args;
	while (1)
	{
		(*argv)[i] = ft_strdup(cur->content);
		if ((*argv)[i] == NULL)
		{
			free_strs(*argv);
			*argv = NULL;
			return (-1);
		}
		i++;
		cur = cur->next;
		if (cur == args)
			break ;
	}
	(*argv)[i] = NULL;
	return (0);
}

static size_t	ms_envp_size(t_envp *ms_envp)
{
	size_t	size;

	size = 0;
	while (ms_envp != NULL)
	{
		size++;
		ms_envp = ms_envp->next;
	}
	return (size);
}

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

static int	set_key_value(char **envp, char *key, char *value)
{
	if (value == NULL && ft_asprintf(envp, "%s=", key) == -1)
		return (-1);
	if (value != NULL && ft_asprintf(envp, "%s=%s", key, value) == -1)
		return (-1);
	return (0);
}

int	make_envp(char ***envp, t_envp *ms_envp)
{
	size_t	i;

	*envp = (char **)malloc(sizeof(char *) * (ms_envp_size(ms_envp) + 1));
	if (*envp == NULL)
		return (-1);
	i = 0;
	while (ms_envp != NULL)
	{
		if (!is_valid_key(ms_envp->key) || !(ms_envp->flag & FLAG_ENV))
		{
			ms_envp = ms_envp->next;
			continue ;
		}
		if (set_key_value(*envp + i, ms_envp->key, ms_envp->value) == -1)
		{
			free_strs(*envp);
			*envp = NULL;
			return (-1);
		}
		i++;
		ms_envp = ms_envp->next;
	}
	(*envp)[i] = NULL;
	return (0);
}
