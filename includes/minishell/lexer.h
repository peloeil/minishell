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
}	t_token_id;

typedef struct
{
	t_token_id	id;
	char		*str;
}	t_token;

int			maybe_part_of_operator(char c);
t_token_id	identify_operator(const char *input, size_t index);
char		*read_operator_string(const char *input, size_t index, t_token_id id);
char		*read_quoted_string(const char *input, size_t index);
char		*read_expandable_string(const char *input, size_t index);
char		*read_unquoted_string(const char *input, size_t index);
t_list		*tokenize_input(const char *input);

#endif // LEXER_H
