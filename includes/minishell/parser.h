/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:37:01 by sota              #+#    #+#             */
/*   Updated: 2025/05/15 01:22:45 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include <minishell/lexer.h>

typedef t_list	t_arg_list;

typedef struct s_ast_node
{
	t_token_id			id;
	t_arg_list			*args;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

t_token_list	*search_token_from_left(
					t_token_id id,
					t_token_list *start,
					t_token_list *end);
t_token_list	*search_token_from_right(
					t_token_id id,
					t_token_list *start,
					t_token_list *end);
t_token_list	*search_redirect_token(
					t_token_list *start,
					t_token_list *end);
int				parse_command(
					t_ast_node **ast,
					t_token_list *start,
					t_token_list *end);
int				parse_tokens(
					t_ast_node **ast,
					t_token_list *start,
					t_token_list *end);
int				ast_push_args(
					t_arg_list **args,
					t_token_list *start,
					t_token_list *end);

#endif // PARSER_H
