/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:22:31 by sota              #+#    #+#             */
/*   Updated: 2025/05/15 00:14:00 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/parser.h>
#include <stdlib.h>

int	found_parse_error(t_ast_node *ast)
{
	if (ast->id == PARSE_ERROR)
		return (-1);
	if (ast->left != NULL && found_parse_error(ast->left) == -1)
		return (-1);
	if (ast->right != NULL && found_parse_error(ast->right) == -1)
		return (-1);
	return (0);
}

void	free_ast(t_ast_node *ast)
{
	if (ast->left != NULL)
		free_ast(ast->left);
	if (ast->right != NULL)
		free_ast(ast->right);
	ft_list_clear(&ast->args, free);
	free(ast);
}
