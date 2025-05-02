/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:37:01 by sota              #+#    #+#             */
/*   Updated: 2025/05/02 16:37:26 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <minishell/lexer.h>

typedef struct s_ast_node
{
	t_token_id			id;
	t_list				*args;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

t_list		*search_token_from_left(t_token_id id, t_list *start, t_list *end);
t_list		*search_token_from_right(t_token_id id, t_list *start, t_list *end);
t_ast_node	*parse_tokens(t_list *start, t_list *end);
t_ast_node	*parse_command(t_list *start, t_list *end);

#endif // PARSER_H
