/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:55:00 by sota              #+#    #+#             */
/*   Updated: 2025/05/16 21:54:24 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <minishell/expand.h>
#include <libft/ft_ctype.h>
#include <libft/ft_string.h>
#include <stdlib.h>

static int	dollar_as_prefix(const char *str, size_t index)
{
	if (str[index] != '$')
		return (0);
	if (str[index + 1] == '\0')
		return (0);
	if (str[index + 1] == ' ' || str[index + 1] == '\t')
		return (0);
	return (1);
}

static int	change_quote_state(char *quote_char, const char *str, size_t *index)
{
	if ((str[*index] == '\'' && (*quote_char == 0 || *quote_char == '\''))
		|| (str[*index] == '\"' && (*quote_char == 0 || *quote_char == '\"')))
	{
		if (*quote_char == 0)
			*quote_char = str[*index];
		else
			*quote_char = 0;
		(*index)++;
		return (1);
	}
	return (0);
}

int	expand_arg(t_arg_list *arg, const t_envp *envp)
{
	char		quote_char;
	size_t		index;
	char		*str;
	t_string	after;
	int			cond;

	quote_char = 0;
	index = 0;
	str = (char *)arg->content;
	if (ft_str_new(&after) == -1)
		return (-1);
	while (str[index] != '\0')
	{
		if (change_quote_state(&quote_char, str, &index))
			continue ;
		cond = ((quote_char == 0 || quote_char == '\"')
				&& dollar_as_prefix(str, index));
		if (cond && push_expanded_str(&after, str, &index, envp) == -1)
			return (-1);
		if (!cond && ft_str_push(&after, str[index++]) == -1)
			return (-1);
	}
	free(str);
	arg->content = after.str;
	return (0);
}

static int	expand_args(t_arg_list *args, const t_envp *envp)
{
	t_arg_list	*cur;

	cur = args;
	while (1)
	{
		if (expand_arg(cur, envp) == -1)
			return (-1);
		cur = cur->next;
		if (cur == args)
			break ;
	}
	return (0);
}

int	expand_variables(t_ast_node *ast, const t_envp *envp)
{
	if (ast->left == NULL)
		return (expand_args(ast->args, envp));
	if (expand_variables(ast->left, envp) == -1)
		return (-1);
	if (expand_variables(ast->right, envp) == -1)
		return (-1);
	return (expand_args(ast->args, envp));
}
