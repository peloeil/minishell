/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:54:45 by sota              #+#    #+#             */
/*   Updated: 2025/05/06 16:09:22 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <minishell/minishell.h>
# include <minishell/parser.h>

# define READ_FD 0
# define WRITE_FD 1

int	execute_ast(t_ast_node *ast, int *fds);

#endif // EXECUTE_H
