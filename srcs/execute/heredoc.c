/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:07:26 by sota              #+#    #+#             */
/*   Updated: 2025/06/28 22:05:08 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_stdio.h>
#include <libft/ft_string.h>
#include <minishell/expand.h>
#include <minishell/minishell.h>
#include <minishell/signal.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>

#define HEREDOC_PREFIX "/tmp/heredoc"

static int	eof_detected(char *str, const char *delimiter)
{
	if (str != NULL)
		return (0);
	ft_dprintf(STDERR_FILENO,
		"minishell: warning: \
here-document delimited by end-of-file (wanted `%s')\n",
		delimiter);
	return (1);
}

static int	write_heredoc_file(const char *file, const char *delimiter,
		t_envp *envp)
{
	int			fd;
	t_arg_list	line;

	fd = wrap_open(file, O_WRONLY | O_CREAT | O_TRUNC);
	if (fd == -1)
		return (-1);
	rl_event_hook = heredoc_sig_hook;
	while (1)
	{
		line.content = readline("> ");
		if (eof_detected((char *)line.content, delimiter))
			break ;
		if (heredoc_sig_hook() != 0 || ft_strcmp(line.content, delimiter) == 0
			|| expand_arg(&line, envp) == -1 || ft_dprintf(fd, "%s\n",
				(char *)line.content) == -1)
		{
			free(line.content);
			break ;
		}
	}
	close(fd);
	rl_event_hook = sig_hook;
	return (0);
}

static char	*heredoc_filename(void)
{
	char	*filename;
	char	suffix[17];
	size_t	i;
	int		rngfd;

	rngfd = open("/dev/urandom", O_RDONLY);
	if (rngfd == -1)
		return (NULL);
	i = 0;
	while (i < sizeof(suffix) - 1 && read(rngfd, suffix + i, 1) != -1)
	{
		suffix[i] = (char)('a' + (unsigned char)(suffix[i]) % 26);
		i++;
	}
	suffix[i] = '\0';
	if (ft_asprintf(&filename, "%s_%s", HEREDOC_PREFIX, suffix) == -1)
	{
		close(rngfd);
		return (NULL);
	}
	close(rngfd);
	return (filename);
}

int	open_heredoc(const char *delimiter, t_envp *envp)
{
	char	*filename;
	int		fd;

	filename = heredoc_filename();
	if (filename == NULL || write_heredoc_file(filename, delimiter, envp) == -1)
	{
		free(filename);
		return (-1);
	}
	fd = wrap_open(filename, O_RDONLY);
	if (fd == -1)
	{
		free(filename);
		return (-1);
	}
	if (wrap_unlink(filename) == -1 || g_received_signal != 0)
	{
		free(filename);
		close(fd);
		return (-1);
	}
	return (fd);
}
