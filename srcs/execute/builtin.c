/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:23:05 by sota              #+#    #+#             */
/*   Updated: 2025/05/11 20:49:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/parser.h>
#include <minishell/execute.h>
#include <libft/ft_string.h>
#include <libft/ft_stdio.h>

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (2);
	if (ft_strcmp(cmd, "export") == 0)
		return (3);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (4);
	if (ft_strcmp(cmd, "cd") == 0)
		return (5);
	if (ft_strcmp(cmd, "unset") == 0)
		return (6);
	return (0);
}

int	execute_builtin(t_arg_list *args, t_proc_state *state, t_envp *ms_envp)
{
	char	**argv;
	char	**envp;

	if (make_argv(&argv, args) == -1)
		return (-1);
	if (make_envp(&envp, ms_envp) == -1)
	{
		free_strs(argv);
		return (-1);
	}
	if (ft_strcmp(args->content, "pwd") == 0)
		state->status = pwd();
	if (ft_strcmp(args->content, "echo") == 0)
		state->status = echo(state->iofd[OUTFD_INDEX], argv);
	if (ft_strcmp(args->content, "export") == 0)
		state->status = export(state->iofd[OUTFD_INDEX], argv, ms_envp);
	if (ft_strcmp(args->content, "env") == 0)
		state->status = env(state->iofd[OUTFD_INDEX], ms_envp);
	if (ft_strcmp(args->content, "cd") == 0)
		state->status = cd(argv, ms_envp);
	if (ft_strcmp(args->content, "unset") == 0)
		state->status = unset(argv, &ms_envp);
	free_strs(argv);
	free_strs(envp);
	return (0);
}
