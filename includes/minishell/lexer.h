#ifndef LEXER_H
# define LEXER_H

#include <libft/ft_list.h>

typedef enum
{
	PIPE, // |
	LESS, // <
	GREAT, // >
	DLESS, // <<
	DGREAT, // >>
	LESSAND, // <&
	GREATAND, // >&
	TOKEN,
	COMMAND,
	PARSE_ERROR,
}	t_token_id;

typedef struct
{
	t_token_id	id;
	char		*str;
}	t_token;

t_token_id	identify_operator(const char *input, size_t index);
char		*read_operator(const char *input, size_t index);
char		*read_string(const char *input, size_t index);
t_list		*tokenize_input(const char *input);

#endif // LEXER_H
