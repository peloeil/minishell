#include <libft/ft_string.h>

char	*read_quoted_string(const char *input, size_t index)
{
	char	*pos;

	pos = ft_strchr(input + index + 1, input[index]);
	if (pos == NULL)
		return (NULL);
	return (ft_strndup(input + index, pos + 1 - input - index));
}
