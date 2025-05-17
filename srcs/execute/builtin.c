/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/10 16:23:05 by sota              #+#    #+#             */
/*   Updated: 2025/05/17 17:23:03 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_stdio.h>
#include <libft/ft_string.h>
#include <minishell/execute.h>
#include <minishell/parser.h>

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
	if (ft_strcmp(cmd, "exit") == 0)
		return (7);
	return (0);
}

void	init_builtin_func(int (*builtin_func[8])(int, char **, t_envp **))
{
	builtin_func[1] = echo;
	builtin_func[2] = env;
	builtin_func[3] = export;
	builtin_func[4] = pwd;
	builtin_func[5] = cd;
	builtin_func[6] = unset;
	builtin_func[7] = builtin_exit;
}

int	execute_builtin(t_arg_list *args, t_proc_state *state, t_envp *ms_envp)
{
	char			**argv;
	char			**envp;
	t_exit_status	status;
	int				index;
	int				(*builtin_func[8])(int, char **, t_envp **);

	init_builtin_func(builtin_func);
	envp = NULL;
	if (state->iofd[INFD_INDEX] == -1 || state->iofd[OUTFD_INDEX] == -1)
		return (-1);
	if (make_argv(&argv, args) == -1 || make_envp(&envp, ms_envp) == -1)
	{
		free_strs(argv);
		free_strs(envp);
		return (-1);
	}
	index = is_builtin(args->content);
	status = builtin_func[index](state->iofd[OUTFD_INDEX], argv, &ms_envp);
	free_strs(argv);
	free_strs(envp);
	return (update_exit_status(status, ms_envp));
}
