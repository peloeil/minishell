/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 20:23:41 by sota              #+#    #+#             */
/*   Updated: 2025/06/03 20:59:02 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <minishell/parser.h>
#include <minishell/execute.h>
#include <libft/ft_string.h>
#include <libft/ft_stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static int	clean_up(
				int status,
				t_proc_state state,
				t_envp *ms_envp,
				t_ast_node *top)
{
	if (status == -1)
		status = STATUS_ERRORS;
	if (status == -2)
		status = ft_atoi(ft_getenv("?", ms_envp));
	wrap_close(&state.iofd[INFD_INDEX], INFD_INDEX);
	wrap_close(&state.iofd[OUTFD_INDEX], OUTFD_INDEX);
	free_ms_envp(ms_envp);
	free_ast(top);
	return (status);
}

int	child_process(
		t_arg_list *args,
		t_proc_state *state,
		t_envp *ms_envp,
		t_ast_node *top)
{
	char	**argv;
	char	**envp;
	int		status;

	if (set_child_fds(state) == -1)
		exit(clean_up(STATUS_ERRORS, *state, ms_envp, top));
	if (is_builtin(args->content))
	{
		status = execute_builtin(args, state, &ms_envp);
		exit(clean_up(status, *state, ms_envp, top));
	}
	envp = NULL;
	if (make_argv(&argv, args) == -1 || make_envp(&envp, ms_envp) == -1)
	{
		free_strs(argv);
		free_strs(envp);
		exit(clean_up(STATUS_ERRORS, *state, ms_envp, top));
	}
	status = set_command_path(&argv[0], args->content, ms_envp);
	if (status == 0)
	{
		execve(argv[0], argv, envp);
		error_return(0, argv[0], strerror(errno));
	}
	free_strs(argv);
	free_strs(envp);
	exit(clean_up(status, *state, ms_envp, top));
}
