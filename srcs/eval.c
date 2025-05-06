/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:11:44 by marvin            #+#    #+#             */
/*   Updated: 2025/05/06 15:53:54 by sota             ###   ########.fr       */
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
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int	handle_builtin_command(char **argv, t_envp *envp)
{
	if (ft_strcmp(argv[0], "pwd") == 0)
		return (pwd());
	if (ft_strcmp(argv[0], "export") == 0)
		return (export(STDOUT_FILENO, argv, envp));
	if (ft_strcmp(argv[0], "env") == 0)
		return (env(STDOUT_FILENO, envp));
	return (-2);
}

int	handle_external_command(char **argv, const t_envp *envp)
{
	char	*cmd_path;
	int		status;
	pid_t	pid;

	status = set_cmd_path(&cmd_path, argv[0], envp);
	if (status == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		free(cmd_path);
		return (-1);
	}
	if (pid == 0)
	{
		execve(cmd_path, argv, NULL);
		exit(1);
	}
	wait(NULL);
	free(cmd_path);
	return (0);
}

int	eval_cmd(const char *cmd, t_envp *ms_envp)
{
	t_token_list	*tokens;
	t_ast_node		*ast;
	int				parse_failed;
	int				status;

	tokens = tokenize_input(cmd);
	ast = parse_tokens(tokens, tokens->prev);
	parse_failed = check_parse_error(ast);
	free_tokens(tokens, parse_failed);
	if (parse_failed)
	{
		free_ast(ast, parse_failed);
		return (-1);
	}
	if (expand_variables(ast, ms_envp) == -1)
	{
		free_ast(ast, parse_failed);
		return (-1);
	}
	status = execute_ast(ast, ms_envp);
	free_ast(ast, parse_failed);
	return (status);
}
