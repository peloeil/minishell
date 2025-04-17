#include <minishell/lexer.h>

const t_token	*ms_lexer(const char *cmd)
{
	(void)cmd;
	return (&(t_token){ "", COMMAND });
}
