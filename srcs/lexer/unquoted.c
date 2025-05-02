#include <minishell/lexer.h>
#include <libft/ft_string.h>
#include <libft/std_string.h>
#include <stdlib.h>

static int	is_blank(char c)
{
	return (c == ' ' || c == '\t');
}

char	*read_string(const char *input, size_t index)
{
	t_string	str;
	int			in_quote;
	char		c;

	ft_str_new(&str);
	in_quote = 0;
	while (1)
	{
		c = input[index];
		if (c == '\0' || (!in_quote && is_blank(c)))
			break ;
		if (!in_quote && identify_operator(input, index) != TOKEN)
			break ;
		ft_str_push(&str, c);
		if (c == '\"' || c == '\'')
		{
			if (!in_quote)
				in_quote = (int)c;
			else if (in_quote == c)
				in_quote = 0;
		}
		index++;
	}
	if (in_quote)
	{
		free(str.str);
		return (NULL);
	}
	return (str.str);
}
