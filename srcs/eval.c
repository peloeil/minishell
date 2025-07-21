/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:11:44 by marvin            #+#    #+#             */
/*   Updated: 2025/06/28 21:54:57 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <minishell/execute.h>
#include <minishell/expand.h>
#include <minishell/lexer.h>
#include <minishell/minishell.h>
#include <minishell/parser.h>
#include <minishell/signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

static void	init_proc_state(t_proc_state *state)
{
	state->pid = 0;
	state->nproc = 0;
	state->pipefd[READ_PIPE] = STDIN_FILENO;
	state->pipefd[WRITE_PIPE] = STDOUT_FILENO;
	state->iofd[INFD_INDEX] = STDIN_FILENO;
	state->iofd[OUTFD_INDEX] = STDOUT_FILENO;
}

int	wait_children(t_proc_state *state, t_envp **envp)
{
	pid_t			pid;
	int				wstatus;
	t_exit_status	exit_status;

	if (state->nproc == 0 && heredoc_signal(-1) == SIGINT)
	{
		heredoc_signal(0);
		return (update_exit_status(STATUS_SIG_BASE + SIGINT, envp));
	}
	if (state->nproc == 0)
		return (0);
	exit_status = STATUS_ERRORS;
	while (state->nproc--)
	{
		pid = wrap_wait(&wstatus);
		if (pid == -1 || pid != state->pid)
			continue ;
		if (WIFEXITED(wstatus))
			exit_status = WEXITSTATUS(wstatus);
		if (WIFSIGNALED(wstatus) && WTERMSIG(wstatus) == SIGQUIT)
			write(STDERR_FILENO, "Quit (core dumped)\n", 19);
		if (WIFSIGNALED(wstatus))
			exit_status = STATUS_SIG_BASE + WTERMSIG(wstatus);
	}
	return (update_exit_status(exit_status, envp));
}

static int	make_ast_from_str(t_ast_node **ast, const char *cmd)
{
	t_token_list	*tokens;
	int				failed;

	*ast = NULL;
	failed = (tokenize_input(&tokens, cmd) == -1);
	free((void *)cmd);
	if (failed)
		return (-1);
	if (tokens == NULL)
		return (0);
	failed = (parse_tokens(ast, tokens, tokens->prev) == -1);
	free_tokens(tokens);
	if (failed)
		return (-1);
	return (0);
}

int	evaluate_command(const char *cmd, t_envp **envp)
{
	t_ast_node		*ast;
	t_proc_state	state;
	int				status;

	if (make_ast_from_str(&ast, cmd) == -1)
		return (-1);
	if (ast == NULL)
		return (0);
	if (found_parse_error(ast) == -1
		|| expand_variables(ast, *envp) == -1)
	{
		free_ast(ast);
		return (-1);
	}
	init_proc_state(&state);
	status = execute_ast(ast, &state, envp, ast);
	free_ast(ast);
	if (wait_children(&state, envp) == -1 || status == -1)
		return (-1);
	return (status);
}
