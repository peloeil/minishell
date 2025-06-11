/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:07:26 by sota              #+#    #+#             */
/*   Updated: 2025/06/11 15:24:46 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <minishell/expand.h>
#include <libft/ft_string.h>
#include <libft/ft_stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <signal.h>
#include <sys/wait.h>

#define HEREDOC_PREFIX "/tmp/heredoc"
#define EXIT_STATUS_INVALID 128

static volatile sig_atomic_t g_sig = 0;

static void	heredoc_sigint_handler(int sig)
{
	g_sig = sig;
}

static void	heredoc_sigquit_handler(int sig)
{
	(void)sig;
}

static int	here_document_rl_event_hook(void)
{
	if (g_sig == SIGINT)
		rl_done = 1;
	return (0);
}

static void	heredoc_child_signal_setting(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_handler = heredoc_sigint_handler;
	sa_int.sa_flags = 0;
	sigaction(SIGINT, &sa_int, NULL);

	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_handler = heredoc_sigquit_handler;
	sa_quit.sa_flags = 0;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

static void	heredoc_print_error_message(const char *delimiter)
{
	ft_dprintf(STDERR_FILENO, 
		"minishell: warning: here-document delimited by end-of-file (wanted `%s')\n", 
		delimiter);
}

static void	print_line(char *line, int fd)
{
	ft_dprintf(fd, "%s\n", line);
	free(line);
}

static unsigned char	heredoc_child_process(const char *delimiter, int fds[2],
		t_envp *envp)
{
	char	*line;
	t_arg_list	arg_line;

	heredoc_child_signal_setting();
	rl_event_hook = here_document_rl_event_hook;
	close(fds[0]);

	while (1)
	{
		line = readline("> ");
		if (line == NULL)
			heredoc_print_error_message(delimiter);
		if (g_sig == SIGINT)
		{
			rl_done = 0;
			close(fds[1]);
			free(line);
			return (EXIT_STATUS_INVALID + SIGINT);
		}
		if (line == NULL || ft_strcmp(delimiter, line) == 0)
		{
			free(line);
			break;
		}
		arg_line.content = line;
		if (expand_arg(&arg_line, envp) == -1)
		{
			free(line);
			close(fds[1]);
			return (EXIT_FAILURE);
		}	
		print_line((char *)arg_line.content, fds[1]);
	}
	close(fds[1]);
	return (EXIT_SUCCESS);
}

static int	heredoc_parent_process(int fds[2], pid_t pid)
{
	int					status;
	struct sigaction	old_sigint;
	struct sigaction	sa_ignore;
	
	sigemptyset(&sa_ignore.sa_mask);
	sa_ignore.sa_handler = SIG_IGN;
	sa_ignore.sa_flags = 0;
	sigaction(SIGINT, &sa_ignore, &old_sigint);
	waitpid(pid, &status, 0);
	sigaction(SIGINT, &old_sigint, NULL);	
	if (WEXITSTATUS(status) == (EXIT_STATUS_INVALID + SIGINT))
	{
		close(fds[0]);
		close(fds[1]);
		return (-1);
	}
	close(fds[1]);
	return (fds[0]);
}

static int	setup_heredoc(const char *delimiter, t_envp *envp)
{
	int		fds[2];
	pid_t	pid;
	
	if (pipe(fds) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
	{
		close(fds[0]);
		close(fds[1]);
		return (-1);
	}

	if (pid == 0)
	{
		unsigned char exit_status = heredoc_child_process(delimiter, fds, envp);
		exit(exit_status);
	}
	return (heredoc_parent_process(fds, pid));
}

static char	*heredoc_filename(void)
{
	char	*filename;
	char	suffix[16];
	int		rngfd;

	suffix[sizeof(suffix) - 1] = '\0';
	rngfd = open("/dev/urandom", O_RDONLY);
	if (rngfd == -1)
		return (NULL);
	if (read(rngfd, suffix, sizeof(suffix) - 1) == -1
		|| ft_asprintf(&filename, "%s_%s", HEREDOC_PREFIX, suffix) == -1)
	{
		close(rngfd);
		return (NULL);
	}
	close(rngfd);
	return (filename);
}

static int	copy_pipe_to_file(int pipe_fd, const char *filename)
{
	int		file_fd;
	char	buffer[4096];
	ssize_t	bytes_read;
	ssize_t	bytes_written;

	file_fd = wrap_open(filename, O_WRONLY | O_CREAT | O_TRUNC);
	if (file_fd == -1)
		return (-1);
	while ((bytes_read = read(pipe_fd, buffer, sizeof(buffer))) > 0)
	{
		bytes_written = write(file_fd, buffer, bytes_read);
		if (bytes_written != bytes_read)
		{
			close(file_fd);
			return (-1);
		}
	}
	close(file_fd);
	return (bytes_read == 0 ? 0 : -1);
}

int	open_heredoc(const char *delimiter, t_envp *envp)
{
	char	*filename;
	int		pipe_fd;
	int		file_fd;

	pipe_fd = setup_heredoc(delimiter, envp);
	if (pipe_fd == -1)
		return (-1);
	filename = heredoc_filename();
	if (filename == NULL)
	{
		close(pipe_fd);
		return (-1);
	}
	if (copy_pipe_to_file(pipe_fd, filename) == -1)
	{
		close(pipe_fd);
		free(filename);
		return (-1);
	}
	close(pipe_fd);
	file_fd = wrap_open(filename, O_RDONLY);
	if (file_fd == -1)
	{
		free(filename);
		return (-1);
	}
	if (wrap_unlink(filename) == -1)
	{
		free(filename);
		close(file_fd);
		return (-1);
	}
	free(filename);
	return (file_fd);
}
