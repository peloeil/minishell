/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:54:45 by sota              #+#    #+#             */
/*   Updated: 2025/05/15 03:00:34 by sota             ###   ########.fr       */
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
	STATUS_ERRORS = 1,
	STATUS_NOT_EXECUTABLE = 126,
	STATUS_CMD_NOT_FOUND = 127,
	STATUS_INVALID_EXIT = 128,
	STATUS_SIGINT = STATUS_INVALID_EXIT + 2,
	STATUS_SIGQUIT = STATUS_INVALID_EXIT + 3,
}	t_exit_status;

typedef struct s_proc_state
{
	pid_t			pid;
	size_t			nproc;
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
int	execute_ast(
		t_ast_node *ast,
		t_proc_state *state,
		t_envp *envp,
		t_ast_node *top);
int	child_process(
		t_arg_list *args,
		t_proc_state *state,
		t_envp *ms_envp,
		t_ast_node *top);
int	update_exit_status(t_exit_status status, t_envp *envp);

#endif // EXECUTE_H
