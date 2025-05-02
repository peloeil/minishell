/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:49:51 by sota              #+#    #+#             */
/*   Updated: 2025/05/02 18:35:07 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/parser.h>
#include <libft/ft_stdlib.h>

static t_token_list	*search_redirect_token(
						t_token_list *start,
						t_token_list *end)
{
	t_token_list	*cur;
	t_token_id		id;

	cur = start;
	while (1)
	{
		id = ((t_token *)cur->content)->id;
		if (id == LESS
			|| id == GREAT
			|| id == DLESS
			|| id == DGREAT
			|| id == LESSAND
			|| id == GREATAND)
			return (cur);
		if (cur == end)
			break ;
		cur = cur->next;
	}
	return (NULL);
}

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
	redirect = search_redirect_token(start, end);
	node_to_head(redirect, start);
}

static void	push_args(t_ast_node *ast, t_token_list *start, t_token_list *end)
{
	t_token_list	*cur;

	cur = start;
	while (1)
	{
		ft_list_push_back(&ast->args, ft_list_new(cur->content));
		if (cur == end)
			break ;
		cur = cur->next;
	}
}

t_ast_node	*parse_command(t_token_list *start, t_token_list *end)
{
	t_ast_node		*ast;
	t_token_list	*redirect;

	ast = ft_calloc(1, sizeof(t_ast_node));
	redirect = search_redirect_token(start, end);
	if (redirect == NULL)
	{
		ast->id = COMMAND;
		push_args(ast, start, end);
		return (ast);
	}
	if (redirect == end)
	{
		ast->id = PARSE_ERROR;
		return (ast);
	}
	redirects_to_head(start, end);
	ast->id = ((t_token *)start->content)->id;
	push_args(ast, start, start);
	ast->left = ft_calloc(1, sizeof(t_ast_node));
	ast->left->id = ((t_token *)start->next->content)->id;
	push_args(ast->left, start->next, start->next);
	if (start->next != end)
		ast->right = parse_command(start->next->next, end);
	return (ast);
}
