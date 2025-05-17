/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:20:05 by sota              #+#    #+#             */
/*   Updated: 2025/05/14 15:55:11 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <minishell/execute.h>
#include <fcntl.h>
#include <unistd.h>

static int	close_old_fds(t_proc_state *state, int fd)
{
	if (fd == STDIN_FILENO)
	{
		if (state->iofd[INFD_INDEX] == state->pipefd[READ_PIPE])
		{
			wrap_close(&state->iofd[INFD_INDEX], STDIN_FILENO);
			wrap_close(&state->pipefd[READ_PIPE], STDIN_FILENO);
		}
	}
	else
	{
		if (state->iofd[OUTFD_INDEX] == state->pipefd[WRITE_PIPE])
		{
			wrap_close(&state->iofd[OUTFD_INDEX], STDOUT_FILENO);
			wrap_close(&state->pipefd[WRITE_PIPE], STDOUT_FILENO);
		}
	}
	return (0);
}

int	set_redirect_fd(t_token_id id, char *file, t_proc_state *state)
{
	int	fd;

	fd = -1;
	if (id == LESS || id == LESSAND)
	{
		fd = open(file, O_RDONLY);
		if (fd == -1)
			return (-1);
		close_old_fds(state, STDIN_FILENO);
		state->iofd[INFD_INDEX] = fd;
		return (0);
	}
	if (id == GREAT || id == GREATAND)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (id == DGREAT)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		return (-1);
	close_old_fds(state, STDIN_FILENO);
	state->iofd[OUTFD_INDEX] = fd;
	return (0);
}

int	set_parent_fds(t_proc_state *state)
{
	wrap_close(&state->iofd[INFD_INDEX], STDIN_FILENO);
	wrap_close(&state->iofd[OUTFD_INDEX], STDOUT_FILENO);
	wrap_close(&state->pipefd[WRITE_PIPE], STDOUT_FILENO);
	return (0);
}

int	set_child_fds(t_proc_state *state)
{
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
