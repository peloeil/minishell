/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 00:03:53 by sota              #+#    #+#             */
/*   Updated: 2025/05/14 15:58:26 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <minishell/parser.h>
#include <minishell/execute.h>
#include <libft/ft_string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

static int	execute_command(t_arg_list *args, t_proc_state *state, t_envp *envp)
{
	if (is_builtin(args->content))
		return (execute_builtin(args, state, envp));
	state->nproc++;
	state->pid = wrap_fork();
	if (state->pid == -1)
		return (-1);
	if (state->pid == 0)
		return (child_process(args, state, envp));
	return (set_parent_fds(state));
}

static int	execute_nopipe(t_ast_node *ast, t_proc_state *state, t_envp *envp)
{
	if (ast->id == COMMAND)
		return (execute_command(ast->args, state, envp));
	if (set_redirect_fd(ast->id, ast->left->args->content, state) == -1)
		return (-1);
	return (execute_nopipe(ast->right, state, envp));
}

static int	execute_pipe(t_ast_node *ast, t_proc_state *state, t_envp *envp)
{
	if (pipe(state->pipefd) == -1)
		return (-1);
	state->iofd[OUTFD_INDEX] = state->pipefd[WRITE_PIPE];
	execute_nopipe(ast->left, state, envp);
	state->iofd[INFD_INDEX] = state->pipefd[READ_PIPE];
	return (execute_ast(ast->right, state, envp));
}

int	execute_ast(t_ast_node *ast, t_proc_state *state, t_envp *envp)
{
	if (ast->id == PIPE)
		return (execute_pipe(ast, state, envp));
	return (execute_nopipe(ast, state, envp));
}
