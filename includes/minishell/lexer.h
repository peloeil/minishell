#ifndef LEXER_H
# define LEXER_H

typedef enum
{
	TOKEN,
	WORD,
	ASSIGNMENT_WORD,
	NAME,
	NEWLINE,
	IO_NUMBER,
	IO_LOCAION,
	LESS,
	GREAT,
	DLESS,
	DGREAT,
	LESSAND,
	GREATAND,
	AND_IF,
	OR_IF,
	LEFT_PARENTHESIS,
	RIGHT_PARENTHESIS,

}	t_token_id;

typedef struct
{
	char		*word;
	t_token_id	id;
}	t_token;

const t_token	*ms_lexer(const char *cmd);

#endif // LEXER_H
