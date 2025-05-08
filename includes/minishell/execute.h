/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:54:45 by sota              #+#    #+#             */
/*   Updated: 2025/05/08 23:33:54 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <minishell/minishell.h>
# include <minishell/parser.h>
# include <sys/types.h>

# define READ_FD 0
# define WRITE_FD 1

int	child_process(
		t_arg_list *args,
		int in_fd,
		int out_fd,
		t_envp *ms_envp);
int	parent_process(pid_t pid, int in_fd, int out_fd);
int	make_argv(char ***argv, t_arg_list *args);
int	make_envp(char ***envp, t_envp *ms_envp);
int	execute_ast(t_ast_node *ast, int *fds, t_envp *envp);

#endif // EXECUTE_H
