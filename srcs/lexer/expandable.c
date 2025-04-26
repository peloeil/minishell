#include <libft/ft_string.h>

char	*read_expandable_string(const char *input, size_t index)
{
	char	*end;

	end = ft_strchr(input + index, '}');
	if (input[index + 1] == '{' && end != NULL)
		return (ft_strndup(input + index, end - input - index + 1));
	end = ft_strchr(input + index, ' ');
	if (end != NULL)
		return (ft_strndup(input + index, end - input - index));
	return (ft_strndup(input + index, ft_strlen(input + index)));
}
