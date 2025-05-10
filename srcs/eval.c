/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 20:11:44 by marvin            #+#    #+#             */
/*   Updated: 2025/05/10 17:39:45 by sota             ###   ########.fr       */
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
	state->status = STATUS_SUCCESS;
	state->pipefd[READ_PIPE] = STDIN_FILENO;
	state->pipefd[WRITE_PIPE] = STDOUT_FILENO;
	state->iofd[INFD_INDEX] = STDIN_FILENO;
	state->iofd[OUTFD_INDEX] = STDOUT_FILENO;
}

static int	update_exit_status(t_exit_status status, t_envp *envp)
{
	char	*argv[3];
	char	str[20];

	if (ft_sprintf(str, "?=%d", (int)status) == -1)
		return (-1);
	argv[0] = "export";
	argv[1] = str;
	argv[2] = NULL;
	if (export(0, argv, envp) == -1)
		return (-1);
	return (0);
}

int	wait_children(t_proc_state *state)
{
	pid_t	pid;
	int		status;

	while (state->nproc--)
	{
		pid = wait(&status);
		if (pid == -1)
			return (-1);
		if (pid != state->pid)
			continue ;
		if (WIFEXITED(status))
			state->status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			state->status = WTERMSIG(status);
		else
			state->status = STATUS_FAILURE;
	}
	return (0);
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
	if (wait_children(&state) == -1
		|| update_exit_status(state.status, envp) == -1)
		return (-1);
	return (0);
}
