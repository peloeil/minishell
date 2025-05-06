/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:54:45 by sota              #+#    #+#             */
/*   Updated: 2025/05/06 15:55:42 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTE_H
# define EXECUTE_H

# include <minishell/minishell.h>
# include <minishell/parser.h>

int	execute_ast(t_ast_node *ast, t_envp *envp);

#endif // EXECUTE_H
