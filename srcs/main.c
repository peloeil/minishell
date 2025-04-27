/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:49:27 by sota              #+#    #+#             */
/*   Updated: 2025/03/11 18:27:22 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <stdlib.h>
#include <stdio.h>
#include <libft/ft_stdio.h>

int	main(int argc, char **argv, char **envp)
{
	char	*cmd_str;

	(void)argc;
	(void)argv;
	while (1)
	{
		cmd_str = wrap_readline(
				PROMPT, isatty(STDIN_FILENO) && isatty(STDERR_FILENO)
				);
		if (cmd_str == NULL)
			break ;
		eval_cmd(cmd_str, (const char **)envp);
		free(cmd_str);
	}
	return (EXIT_SUCCESS);
}
