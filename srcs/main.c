/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/11 17:49:27 by sota              #+#    #+#             */
/*   Updated: 2025/05/15 04:52:57 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <minishell/execute.h>
#include <libft/ft_stdlib.h>
#include <stdlib.h>

int	main(int argc, char **argv, char **envp)
{
	int		status;
	char	*cmd_str;
	t_envp	*ms_envp;

	(void)argc;
	(void)argv;
	if (make_ms_envp(&ms_envp, envp) == -1)
		return (STATUS_ERRORS);
	while (1)
	{
		cmd_str = wrap_readline(PROMPT);
		if (cmd_str == NULL)
			break ;
		if (eval_cmd(cmd_str, ms_envp) == -1)
			update_exit_status(STATUS_ERRORS, ms_envp);
		free(cmd_str);
	}
	status = ft_atoi(ft_getenv("?", ms_envp));
	free_ms_envp(ms_envp);
	return (status);
}
