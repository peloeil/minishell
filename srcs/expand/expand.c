/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:55:00 by sota              #+#    #+#             */
/*   Updated: 2025/05/02 21:29:38 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <minishell/expand.h>
#include <stdlib.h>

static int	expand_args(t_token_list **args, const t_envp *envp)
{
	(void)args;
	(void)envp;
	return (0);
}

int	expand_variables(t_ast_node *ast, const t_envp *envp)
{
	if (ast->left == NULL)
		return (expand_args(&ast->args, envp));
	if (expand_variables(ast->left, envp) == -1)
		return (-1);
	if (expand_variables(ast->right, envp) == -1)
		return (-1);
	return (expand_args(&ast->args, envp));
}
