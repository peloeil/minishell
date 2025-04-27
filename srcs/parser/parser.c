#include <minishell/parser.h>
#include <libft/ft_stdlib.h>

t_ast_node	*parse_tokens(t_list *start, t_list *end)
{
	t_ast_node	*ast;
	t_list		*node;

	ast = ft_calloc(1, sizeof(t_ast_node));
	node = search_token_from_left(PIPE, start, end);
	if (node != NULL && (node == start || node == end))
	{
		ast->token.id = PARSE_ERROR;
		return (ast);
	}
	if (node == NULL)
	{
		ast->token.id = COMMAND;
		return (parse_command(start, end));
	}
	ast->token.id = PIPE;
	ast->left = parse_command(start, node->prev);
	ast->right = parse_tokens(node->next, end);
	return (ast);
}
