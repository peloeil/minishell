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
#include <libft/ft_stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

char	*wrap_readline(const char *prompt)
{
	char	*res;
	size_t	size;

	g_received_signal = 0;
	setup_signal_handler();
	if (isatty(STDIN_FILENO) == -1)
		return (NULL);
	if (isatty(STDERR_FILENO) == -1)
		return (NULL);
	if (isatty(STDIN_FILENO) && isatty(STDERR_FILENO))
		return (readline(prompt));
	size = 0;
	if (ft_getline(&res, &size, STDIN_FILENO) == -1)
		return (NULL);
	res[size - 1] = '\0';
	return (res);
}
