/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 00:03:53 by sota              #+#    #+#             */
/*   Updated: 2025/06/29 12:42:31 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <minishell/parser.h>
#include <minishell/execute.h>
#include <minishell/signal.h>
#include <libft/ft_string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

static int	execute_command(
				t_arg_list *args,
				t_proc_state *state,
				t_envp **envp,
				t_ast_node *top)
{
	int	status;

	if (is_builtin(args->content))
	{
		status = execute_builtin(args, state, envp);
		if (set_parent_fds(state) == -1)
			return (-1);
		return (status);
	}
	state->pid = wrap_fork();
	state->nproc++;
	if (state->pid == -1)
		return (-1);
	if (state->pid == 0)
		return (child_process(args, state, *envp, top));
	return (set_parent_fds(state));
}

static int	execute_nopipe(
				t_ast_node *ast,
				t_proc_state *state,
				t_envp **envp,
				t_ast_node *top)
{
	int	failed;

	failed = 0;
	while (ast != NULL && ast->id != COMMAND)
	{
		if (!failed
			&& set_redirect_fd(ast->id,
				ast->left->args->content,
				state,
				*envp) == -1)
		{
			failed = 1;
			if (heredoc_signal(-1) == SIGINT)
				break ;
		}
		ast = ast->right;
	}
	if (failed || ast == NULL)
		return (set_parent_fds(state));
	return (execute_command(ast->args, state, envp, top));
}

static int	execute_pipe(
				t_ast_node *ast,
				t_proc_state *state,
				t_envp **envp,
				t_ast_node *top)
{
	if (wrap_pipe(state->pipefd) == -1)
		return (-1);
	state->iofd[OUTFD_INDEX] = state->pipefd[WRITE_PIPE];
	execute_nopipe(ast->left, state, envp, top);
	if (heredoc_signal(-1) == SIGINT)
		return (0);
	state->iofd[INFD_INDEX] = state->pipefd[READ_PIPE];
	return (execute_ast(ast->right, state, envp, top));
}

int	execute_ast(
		t_ast_node *ast,
		t_proc_state *state,
		t_envp **envp,
		t_ast_node *top)
{
	if (ast->id == PIPE)
		return (execute_pipe(ast, state, envp, top));
	return (execute_nopipe(ast, state, envp, top));
}
