/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:20:05 by sota              #+#    #+#             */
/*   Updated: 2025/06/27 19:00:46 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <minishell/execute.h>
#include <minishell/signal.h>
#include <signal.h>
#include <fcntl.h>
#include <unistd.h>

static int	close_old_fds(t_proc_state *state, int fd)
{
	if (fd == STDIN_FILENO)
	{
		if (state->iofd[INFD_INDEX] == state->pipefd[READ_PIPE])
			wrap_close(&state->pipefd[READ_PIPE], STDIN_FILENO);
		wrap_close(&state->iofd[INFD_INDEX], STDIN_FILENO);
	}
	else
	{
		if (state->iofd[OUTFD_INDEX] == state->pipefd[WRITE_PIPE])
			wrap_close(&state->pipefd[WRITE_PIPE], STDOUT_FILENO);
		wrap_close(&state->iofd[OUTFD_INDEX], STDOUT_FILENO);
	}
	return (0);
}

int	set_redirect_fd(
		t_token_id id,
		char *file,
		t_proc_state *state,
		t_envp *envp)
{
	int	fd;
	int	oldfd;

	fd = -1;
	oldfd = STDIN_FILENO;
	if (id == LESS)
		fd = wrap_open(file, O_RDONLY);
	if (id == DLESS)
		fd = open_heredoc(file, envp);
	if (id == GREAT || id == DGREAT)
		oldfd = STDOUT_FILENO;
	if (id == GREAT)
		fd = wrap_open(file, O_WRONLY | O_CREAT | O_TRUNC);
	if (id == DGREAT)
		fd = wrap_open(file, O_WRONLY | O_CREAT | O_APPEND);
	close_old_fds(state, oldfd);
	state->iofd[oldfd] = fd;
	if (fd == -1)
		return (-1);
	return (0);
}

int	set_parent_fds(t_proc_state *state)
{
	wrap_close(&state->iofd[INFD_INDEX], STDIN_FILENO);
	wrap_close(&state->iofd[OUTFD_INDEX], STDOUT_FILENO);
	wrap_close(&state->pipefd[WRITE_PIPE], STDOUT_FILENO);
	if (heredoc_signal(-1) == SIGINT)
		wrap_close(&state->pipefd[READ_PIPE], STDIN_FILENO);
	return (0);
}

int	set_child_fds(t_proc_state *state)
{
	if (state->iofd[INFD_INDEX] == -1 || state->iofd[OUTFD_INDEX] == -1)
		return (-1);
	if (state->iofd[INFD_INDEX] != STDIN_FILENO
		&& wrap_dup2(state->iofd[INFD_INDEX], STDIN_FILENO) == -1)
		return (-1);
	if (state->iofd[OUTFD_INDEX] != STDOUT_FILENO
		&& wrap_dup2(state->iofd[OUTFD_INDEX], STDOUT_FILENO) == -1)
		return (-1);
	wrap_close(&state->iofd[INFD_INDEX], STDIN_FILENO);
	wrap_close(&state->iofd[OUTFD_INDEX], STDOUT_FILENO);
	wrap_close(&state->pipefd[READ_PIPE], STDIN_FILENO);
	wrap_close(&state->pipefd[WRITE_PIPE], STDOUT_FILENO);
	return (0);
}
