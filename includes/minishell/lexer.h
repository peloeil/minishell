#ifndef LEXER_H
# define LEXER_H

#include <libft/ft_list.h>

typedef enum
{
	TOKEN,
	WORD,
	ASSIGNMENT_WORD,
	NAME,
	NEWLINE, // \n
	IO_NUMBER, // file descriptor number
	PIPE, // |
	LESS, // <
	GREAT, // >
	DLESS, // <<
	DGREAT, // >>
	LESSAND, // <&
	GREATAND, // >&
	AND_IF, // &&
	OR_IF, // ||
	LEFT_PARENTHESIS, // (
	RIGHT_PARENTHESIS, // )
}	t_token_id;

typedef struct
{
	t_token_id	id;
	char		*str;
}	t_token;

t_list	*tokenize_input(const char *input);

#endif // LEXER_H
