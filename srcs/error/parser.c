/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:22:31 by sota              #+#    #+#             */
/*   Updated: 2025/05/06 15:50:57 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/parser.h>
#include <stdlib.h>

int	check_parse_error(t_ast_node *ast)
{
	if (ast->id == PARSE_ERROR)
		return (1);
	if (ast->left != NULL && check_parse_error(ast->left))
		return (1);
	if (ast->right != NULL && check_parse_error(ast->right))
		return (1);
	return (0);
}

void	free_ast(t_ast_node *ast, int parse_failed)
{
	if (ast->left != NULL)
		free_ast(ast->left, parse_failed);
	if (ast->right != NULL)
		free_ast(ast->right, parse_failed);
	if (parse_failed)
		ft_list_clear(&ast->args, NULL);
	else
		ft_list_clear(&ast->args, free);
	free(ast);
}
