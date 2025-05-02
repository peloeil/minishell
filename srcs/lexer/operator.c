/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:41:19 by sota              #+#    #+#             */
/*   Updated: 2025/05/02 16:41:20 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/lexer.h>
#include <libft/ft_string.h>

t_token_id	identify_operator(const char *input, size_t index)
{
	if (ft_strncmp(input + index, "<<", 2) == 0)
		return (DLESS);
	if (ft_strncmp(input + index, ">>", 2) == 0)
		return (DGREAT);
	if (ft_strncmp(input + index, "<&", 2) == 0)
		return (LESSAND);
	if (ft_strncmp(input + index, ">&", 2) == 0)
		return (GREATAND);
	if (ft_strncmp(input + index, "|", 1) == 0)
		return (PIPE);
	if (ft_strncmp(input + index, "<", 1) == 0)
		return (LESS);
	if (ft_strncmp(input + index, ">", 1) == 0)
		return (GREAT);
	return (TOKEN);
}

char	*read_operator(const char *input, size_t index)
{
	size_t		len;
	t_token_id	id;

	id = identify_operator(input, index);
	if (id == TOKEN)
		return (NULL);
	len = 1;
	if (id == DLESS || id == DGREAT || id == LESSAND || id == GREATAND)
		len++;
	return (ft_strndup(input + index, len));
}
