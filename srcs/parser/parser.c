#include <minishell/parser.h>
#include <libft/ft_stdlib.h>
#include <libft/std_string.h>
#include <stdlib.h>

t_ast_node	*parse_tokens(t_list *start, t_list *end)
{
	t_ast_node	*ast;
	t_list		*node;

	ast = ft_calloc(1, sizeof(t_ast_node));
	node = search_token_from_left(PIPE, start, end);
	if (node != NULL && (node == start || node == end))
	{
		ast->id = PARSE_ERROR;
		return (ast);
	}
	if (node == NULL)
	{
		free(ast);
		return (parse_command(start, end));
	}
	ast->id = PIPE;
	ast->left = parse_command(start, node->prev);
	ast->right = parse_tokens(node->next, end);
	return (ast);
}

t_list	*search_redirect_token(t_list *start, t_list *end)
{
	t_list		*cur;
	t_token_id	id;

	cur = start;
	while (1)
	{
		id = ((t_token *)cur->content)->id;
		if (id == LESS
			|| id == GREAT
			|| id == DLESS
			|| id == DGREAT
			|| id == LESSAND
			|| id == GREATAND)
			return (cur);
		if (cur == end)
			break ;
		cur = cur->next;
	}
	return (NULL);
}


static void	node_to_top(t_list *node, t_list *start)
{
	t_list	*cur;
	t_list	*prev;
	void	*tmp;

	if (node == start)
		return ;
	cur = node;
	prev = node->prev;
	while (1)
	{
		tmp = cur->content;
		cur->content = prev->content;
		prev->content = tmp;
		cur = prev;
		prev = prev->prev;
		if (cur == start)
			break ;
	}
}

void	redirects_to_top(t_list *start, t_list *end)
{
	t_list	*redirect;
	t_list	*file;

	redirect = search_redirect_token(start, end);
	file = redirect->next;
	if (redirect == start && file == end)
		return ;
	node_to_top(file, start);
	node_to_top(redirect, start);
}

t_ast_node	*parse_command(t_list *start, t_list *end)
{
	t_ast_node	*ast;
	t_list		*redirect;
	t_list		*cur;

	ast = ft_calloc(1, sizeof(t_ast_node));
	redirect = search_redirect_token(start, end);
	if (redirect == NULL) // if no redirect
	{
		ast->id = COMMAND;
		cur = start;
		while (1)
		{
			ft_list_push_back(&ast->args, ft_list_new(start->content));
			if (cur == end)
				break ;
			cur = cur->next;
		}
		return (ast);
	}
	if (redirect == end)
	{
		ast->id = PARSE_ERROR;
		return (ast);
	}
	redirects_to_top(start, end);
	ast->id = ((t_token *)start->content)->id;
	ast->left = ft_calloc(1, sizeof(t_ast_node));
	ast->left->id = ((t_token *)start->next->content)->id;
	ft_list_push_back(&ast->left->args, ft_list_new(start->next->content));
	ast->right = NULL;
	if (start->next != end)
		ast->right = parse_command(start->next->next, end);
	return (ast);
}
