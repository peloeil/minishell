/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:40:17 by sota              #+#    #+#             */
/*   Updated: 2025/05/15 00:48:28 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <minishell/parser.h>
#include <libft/ft_stdlib.h>
#include <stdlib.h>

static int	is_head_or_tail(
				t_token_list *node,
				t_token_list *start,
				t_token_list *end)
{
	if (node != NULL && (node == start || node == end))
		return (1);
	return (0);
}

int	parse_tokens(t_ast_node **ast, t_token_list *start, t_token_list *end)
{
	t_token_list	*node;

	*ast = (t_ast_node *)ft_calloc(1, sizeof(t_ast_node));
	if (*ast == NULL)
		return (-1);
	node = search_token_from_left(PIPE, start, end);
	(*ast)->id = PARSE_ERROR;
	if (is_head_or_tail(node, start, end))
		return (0);
	if (node == NULL)
	{
		free_ast(*ast);
		return (parse_command(ast, start, end));
	}
	(*ast)->id = PIPE;
	if (ast_push_args(&(*ast)->args, node, node) == -1
		|| parse_command(&(*ast)->left, start, node->prev) == -1
		|| parse_tokens(&(*ast)->right, node->next, end) == -1)
	{
		free_ast(*ast);
		return (-1);
	}
	return (0);
}
