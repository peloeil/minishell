/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 21:11:31 by sota              #+#    #+#             */
/*   Updated: 2025/05/08 23:35:10 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <minishell/parser.h>
#include <libft/ft_string.h>
#include <libft/ft_stdio.h>
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

int	make_envp(char ***envp, t_envp *ms_envp)
{
	size_t	i;

	*envp = (char **)malloc(sizeof(char *) * (ms_envp_size(ms_envp) + 1));
	if (*envp == NULL)
		return (-1);
	i = 0;
	while (ms_envp != NULL)
	{
		if (ft_asprintf(&(*envp)[i], "%s=%s", ms_envp->key, ms_envp->value) == -1)
		{
			free_strs(*envp);
			return (-1);
		}
		i++;
		ms_envp = ms_envp->next;
	}
	(*envp)[i] = NULL;
	return (0);
}
