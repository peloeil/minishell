/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:53:51 by sota              #+#    #+#             */
/*   Updated: 2025/05/02 20:58:18 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include <minishell/minishell.h>
# include <minishell/parser.h>

int	expand_variables(t_ast_node *ast, const t_envp *envp);

#endif // EXPAND_H
