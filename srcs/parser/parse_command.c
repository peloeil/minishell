/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:49:51 by sota              #+#    #+#             */
/*   Updated: 2025/05/15 01:39:06 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <minishell/parser.h>
#include <libft/ft_stdlib.h>
#include <libft/ft_string.h>
#include <stdlib.h>

static void	node_to_head(t_token_list *node, t_token_list *start)
{
	t_token_list	*cur;
	t_token_list	*prev;
	void			*tmp;

	if (node == start)
		return ;
	cur = node;
	prev = node->prev;
	while (1)
	{
		tmp = cur->content;
		cur->content = prev->content;
		prev->content = tmp;
		cur = prev;
		prev = prev->prev;
		if (cur == start)
			break ;
	}
}

static void	redirects_to_head(t_token_list *start, t_token_list *end)
{
	t_token_list	*redirect;
	t_token_list	*file;

	redirect = search_redirect_token(start, end);
	file = redirect->next;
	node_to_head(file, start);
	redirect = redirect->next;
	node_to_head(redirect, start);
}

int	ast_push_args(t_arg_list **args, t_token_list *start, t_token_list *end)
{
	t_token_list	*cur;
	char			*str;
	t_arg_list		*arg;

	cur = start;
	while (1)
	{
		str = ft_strdup(((t_token *)cur->content)->str);
		arg = ft_list_new(str);
		if (str == NULL || arg == NULL)
		{
			free(str);
			free(arg);
			ft_list_clear(args, free);
			return (-1);
		}
		ft_list_push_back(args, arg);
		if (cur == end)
			break ;
		cur = cur->next;
	}
	return (0);
}

static int	setup_redirect_ast(t_ast_node *ast, t_token_list *start)
{
	t_token_list	*redirect;
	t_token_list	*file;

	redirect = start;
	file = start->next;
	ast->id = ((t_token *)redirect->content)->id;
	ast->left = (t_ast_node *)ft_calloc(1, sizeof(t_ast_node));
	if (ast->left == NULL
		|| ast_push_args(&ast->args, redirect, redirect) == -1
		|| ast_push_args(&ast->left->args, file, file) == -1)
		return (-1);
	ast->left->id = ((t_token *)file->content)->id;
	return (0);
}

int	parse_command(t_ast_node **ast, t_token_list *start, t_token_list *end)
{
	t_token_list	*redirect;

	*ast = (t_ast_node *)ft_calloc(1, sizeof(t_ast_node));
	if (*ast == NULL)
		return (-1);
	redirect = search_redirect_token(start, end);
	(*ast)->id = PARSE_ERROR;
	if (redirect == end)
		return (0);
	if (redirect == NULL)
	{
		(*ast)->id = COMMAND;
		return (ast_push_args(&(*ast)->args, start, end));
	}
	redirects_to_head(start, end);
	if (setup_redirect_ast(*ast, start) == -1)
	{
		free_ast(*ast);
		return (-1);
	}
	if (start->next != end)
		return (parse_command(&(*ast)->right, start->next->next, end));
	return (0);
}
