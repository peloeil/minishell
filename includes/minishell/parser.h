#ifndef PARSER_H
# define PARSER_H

#include <minishell/lexer.h>

typedef struct s_ast_node
{
	t_token				token;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}	t_ast_node;

t_ast_node	*parse_tokens(t_list *start, t_list *end);

#endif // PARSER_H
