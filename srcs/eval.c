/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:11:44 by marvin            #+#    #+#             */
/*   Updated: 2025/05/08 21:14:40 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <minishell/lexer.h>
#include <minishell/parser.h>
#include <minishell/expand.h>
#include <minishell/execute.h>
#include <libft/ft_string.h>
#include <libft/ft_stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int	eval_cmd(const char *cmd, t_envp *envp)
{
	t_token_list	*tokens;
	t_ast_node		*ast;
	int				parse_failed;
	int				status;
	int				fds[2];

	tokens = tokenize_input(cmd);
	ast = parse_tokens(tokens, tokens->prev);
	parse_failed = check_parse_error(ast);
	free_tokens(tokens, parse_failed);
	if (parse_failed || expand_variables(ast, envp) == -1)
	{
		free_ast(ast, parse_failed);
		return (-1);
	}
	fds[READ_FD] = STDIN_FILENO;
	fds[WRITE_FD] = STDOUT_FILENO;
	status = execute_ast(ast, fds, envp);
	free_ast(ast, parse_failed);
	return (status);
}
