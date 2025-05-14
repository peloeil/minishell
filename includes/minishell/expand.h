/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:53:51 by sota              #+#    #+#             */
/*   Updated: 2025/05/15 01:51:35 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPAND_H
# define EXPAND_H

# include <minishell/minishell.h>
# include <minishell/parser.h>

int		push_expanded_str(
			t_string *after,
			char *str,
			size_t *index,
			const t_envp *envp);
int		expand_variables(t_ast_node *ast, const t_envp *envp);

#endif // EXPAND_H
