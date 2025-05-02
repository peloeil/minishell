/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:40:17 by sota              #+#    #+#             */
/*   Updated: 2025/05/02 16:52:46 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/parser.h>
#include <libft/ft_stdlib.h>
#include <stdlib.h>

t_ast_node	*parse_tokens(t_list *start, t_list *end)
{
	t_ast_node	*ast;
	t_list		*node;

	ast = ft_calloc(1, sizeof(t_ast_node));
	node = search_token_from_left(PIPE, start, end);
	if (node != NULL && (node == start || node == end))
	{
		ast->id = PARSE_ERROR;
		return (ast);
	}
	if (node == NULL)
	{
		free(ast);
		return (parse_command(start, end));
	}
	ast->id = PIPE;
	ft_list_push_back(&ast->args, ft_list_new(node->content));
	ast->left = parse_command(start, node->prev);
	ast->right = parse_tokens(node->next, end);
	return (ast);
}
