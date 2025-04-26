#include "strings.h"
#include <minishell/lexer.h>
#include <libft/ft_string.h>
#include <libft/ft_list.h>
#include <libft/ft_stdio.h>
#include <stdlib.h>

static int	is_blank(char c)
{
	return (c == ' ' || c == '\t');
}

static int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

static int	is_dollar(char c)
{
	return (c == '$');
}

int	set_next_token(t_token *token, const char *input, size_t *index)
{
	token->str = NULL;
	while (input[*index] != '\0' && is_blank(input[*index]))
		(*index)++;
	if (input[*index] == '\0')
		return (0);
	if (maybe_part_of_operator(input[*index]))
	{
		token->id = identify_operator(input, *index);
		token->str = read_operator_string(input, *index, token->id);
	}
	else if (is_quote(input[*index]))
	{
		token->id = TOKEN;
		token->str = read_quoted_string(input, *index);
	}
	else if (is_dollar(input[*index]))
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

	tokens = NULL;
	index = 0;
	while (1)
	{
		token = (t_token *)malloc(sizeof(t_token));
		if (set_next_token(token, input, &index) == -1) // syntax error
		{
			ft_printf("syntax error\n");
			exit(EXIT_FAILURE);
		}
		if (token->str == NULL) // 全部トークンを取得
		{
			free(token);
			break ;
		}
		ft_list_push_back(&tokens, ft_list_new(token));
	}
	return (tokens);
}
