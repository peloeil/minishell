/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:23:41 by sota              #+#    #+#             */
/*   Updated: 2025/05/14 17:01:48 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <minishell/parser.h>
#include <minishell/execute.h>
#include <libft/ft_string.h>
#include <unistd.h>
#include <stdlib.h>

int	child_process(t_arg_list *args, t_proc_state *state, t_envp *ms_envp)
{
	char	**argv;
	char	**envp;
	int		failed;

	argv = NULL;
	envp = NULL;
	failed = (set_child_fds(state) == -1);
	if (!failed && is_builtin(args->content))
		return (execute_builtin(args, state, ms_envp));
	failed |= (make_argv(&argv, args) == -1);
	failed |= (make_envp(&envp, ms_envp) == -1);
	if (failed)
	{
		free_strs(argv);
		free_strs(envp);
		return (-1);
	}
	failed |= (set_command_path(&argv[0], args->content, ms_envp) == -1);
	if (!failed)
		execve(argv[0], argv, envp);
	free_strs(argv);
	free_strs(envp);
	exit(EXIT_FAILURE);
	return (-1);
}
