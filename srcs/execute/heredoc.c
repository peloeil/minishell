/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:07:26 by sota              #+#    #+#             */
/*   Updated: 2025/05/17 00:50:39 by sota             ###   ########.fr       */
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

#define HEREDOC_FILE "/tmp/heredoc"

int	open_heredoc(const char *delimeter, t_envp *envp)
{
	int			fd;
	t_arg_list	line;

	fd = wrap_open(HEREDOC_FILE, O_WRONLY | O_CREAT | O_TRUNC);
	if (fd == -1)
		return (-1);
	while (1)
	{
		line.content = readline("> ");
		if (line.content == NULL)
			break ;
		if (ft_strcmp(line.content, delimeter) == 0
			|| expand_arg(&line, envp) == -1
			|| ft_dprintf(fd, "%s\n", (char *)line.content) == -1)
		{
			free(line.content);
			break ;
		}
	}
	close(fd);
	fd = wrap_open(HEREDOC_FILE, O_RDONLY);
	if (fd == -1)
		return (-1);
	if (wrap_unlink(HEREDOC_FILE) == -1)
	{
		close(fd);
		return (-1);
	}
	return (fd);
}
