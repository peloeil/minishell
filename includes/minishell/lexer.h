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
	WORD,
	ASSIGNMENT_WORD,
	NAME,
	IO_NUMBER, // file descriptor number
	PIPELINE,
	COMMAND,
	CMD_NAME,
	CMD_WORD,
	CMD_PREFIX,
	CMD_SUFFIX,
	REDIRECT_LIST,
	IO_REDIRECT,
	IO_FILE,
	FILENAME,
	IO_HERE,
	HERE_END,
	PARSE_ERROR,
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
