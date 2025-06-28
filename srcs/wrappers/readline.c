/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   readline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:58:12 by sota              #+#    #+#             */
/*   Updated: 2025/05/10 17:35:27 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

char	*wrap_readline(const char *prompt)
{
	int		saved_stdout;
	int		saved_stderr;
	int		dev_null;
	char	*res;

	setup_signal_handler();
	if (isatty(STDIN_FILENO) && isatty(STDERR_FILENO))
		return (readline(prompt));
	saved_stdout = dup(STDOUT_FILENO);
	saved_stderr = dup(STDERR_FILENO);
	dev_null = open("/dev/null", O_WRONLY);
	dup2(dev_null, STDOUT_FILENO);
	dup2(dev_null, STDERR_FILENO);
	close(dev_null);
	res = readline(NULL);
	dup2(saved_stdout, STDOUT_FILENO);
	dup2(saved_stderr, STDERR_FILENO);
	close(saved_stdout);
	close(saved_stderr);
	return (res);
}
