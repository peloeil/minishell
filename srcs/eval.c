/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:11:44 by marvin            #+#    #+#             */
/*   Updated: 2025/05/14 21:25:38 by sota             ###   ########.fr       */
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

static void	init_proc_state(t_proc_state *state)
{
	state->pid = 0;
	state->nproc = 0;
	state->pipefd[READ_PIPE] = STDIN_FILENO;
	state->pipefd[WRITE_PIPE] = STDOUT_FILENO;
	state->iofd[INFD_INDEX] = STDIN_FILENO;
	state->iofd[OUTFD_INDEX] = STDOUT_FILENO;
}

int	wait_children(t_proc_state *state, t_envp *envp)
{
	pid_t			pid;
	int				wstatus;
	t_exit_status	exit_status;

	if (state->nproc == 0)
		return (0);
	exit_status = 0;
	while (state->nproc--)
	{
		pid = wait(&wstatus);
		if (pid == -1)
			return (-1);
		if (pid != state->pid)
			continue ;
		if (WIFEXITED(wstatus))
			exit_status = WEXITSTATUS(wstatus);
		else if (WIFSIGNALED(wstatus))
			exit_status = STATUS_INVALID_EXIT + WTERMSIG(wstatus);
		else
			exit_status = STATUS_ERRORS;
	}
	return (update_exit_status(exit_status, envp));
}

int	eval_cmd(const char *cmd, t_envp *envp)
{
	t_token_list	*tokens;
	t_ast_node		*ast;
	t_proc_state	state;
	int				parse_failed;

	tokens = tokenize_input(cmd);
	ast = parse_tokens(tokens, tokens->prev);
	parse_failed = check_parse_error(ast);
	free_tokens(tokens, parse_failed);
	if (parse_failed || expand_variables(ast, envp) == -1)
	{
		free_ast(ast, parse_failed);
		return (-1);
	}
	init_proc_state(&state);
	if (execute_ast(ast, &state, envp) == -1)
	{
		free_ast(ast, parse_failed);
		return (-1);
	}
	free_ast(ast, parse_failed);
	if (wait_children(&state, envp) == -1)
		return (-1);
	return (0);
}
