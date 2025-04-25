#include "strings.h"
#include <minishell/lexer.h>
#include <libft/ft_string.h>
#include <libft/ft_list.h>
#include <stdlib.h>

int	is_quoted(const char *input, size_t i);

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	set_next_token(t_token *token, const char *input, size_t *index)
{
	token->str = NULL;
	while (input[*index] != '\0' && is_blank(input[*index]))
		*index++;
	if (input[*index] == '\0')
		return (0);
	if (is_part_of_operator(input, *index))
	{
		token->id = identify_operator(input, *index);
		token->str = read_operator_string(input, *index, token->id);
	}
	else if (input[*index] == '\'' || input[*index] == '\"')
	{
		token->id = TOKEN;
		token->str = read_quoted_string(input, *index);
	}
	else if (input[*index] == '$')
	{
		token->id = TOKEN;
		token->str = read_expandable_string(input, *index);
	}
	else
	{
		token->id = TOKEN;
		token->str = read_unquoted_string(input, *index);
	}
	if (token->str == NULL) // syntax error
		return (-1);
	*index += ft_strlen(token->str);
	return (0);
}

t_list	*tokenize_input(const char *input)
{
	size_t		index;
	t_token		*token;
	t_list		*tokens;

	token = (t_token *)malloc(sizeof(t_token));
	tokens = NULL;
	index = 0;
	while (1)
	{
		if (set_next_token(token, input, &index) == -1) // syntax error
			exit(EXIT_FAILURE);
		if (token->str == NULL) // 全部トークンを取得
			break ;
		ft_list_push_back(&tokens, ft_list_new(token));
	}
	return (tokens);
}
