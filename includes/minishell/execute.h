/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:54:45 by sota              #+#    #+#             */
/*   Updated: 2025/05/10 16:37:44 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <minishell/minishell.h>
# include <minishell/parser.h>
# include <sys/types.h>

# define INFD_INDEX 0
# define OUTFD_INDEX 1
# define READ_PIPE 0
# define WRITE_PIPE 1

typedef enum e_exit_status
{
	STATUS_SUCCESS = 0,
	STATUS_FAILURE = 1,
}	t_exit_status;

typedef struct s_proc_state
{
	pid_t			pid;
	size_t			nproc;
	t_exit_status	status;
	int				pipefd[2];
	int				iofd[2];
}	t_proc_state;

int	make_argv(char ***argv, t_arg_list *args);
int	make_envp(char ***envp, t_envp *ms_envp);
int	set_redirect_fd(t_token_id id, char *file, t_proc_state *state);
int	set_parent_fds(t_proc_state *state);
int	set_child_fds(t_proc_state *state);
int	is_builtin(char *cmd);
int	execute_builtin(t_arg_list *args, t_proc_state *state, t_envp *ms_envp);
int	child_process(t_arg_list *args, t_proc_state *state, t_envp *ms_envp);
int	execute_ast(t_ast_node *ast, t_proc_state *state, t_envp *envp);

#endif // EXECUTE_H
