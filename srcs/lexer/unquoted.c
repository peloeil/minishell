#include <libft/ft_string.h>

char	*read_unquoted_string(const char *input, size_t index)
{
	char	*pos;

	pos = ft_strchr(input + index, ' ');
	if (pos == NULL)
		return (ft_strdup(input + index));
	return (ft_strndup(input + index, pos - input - index));
}
