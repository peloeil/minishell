/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:37:41 by sota              #+#    #+#             */
/*   Updated: 2025/05/15 01:21:15 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <libft/ft_list.h>

typedef t_list	t_token_list;

typedef enum e_token_id
{
	PIPE,
	LESS,
	GREAT,
	DLESS,
	DGREAT,
	LESSAND,
	GREATAND,
	TOKEN,
	COMMAND,
	PARSE_ERROR,
}	t_token_id;

typedef struct s_token
{
	t_token_id	id;
	char		*str;
}	t_token;

t_token_id	identify_operator(const char *input, size_t index);
char		*read_operator(const char *input, size_t index);
char		*read_string(const char *input, size_t index);
int			tokenize_input(t_token_list **tokens, const char *cmd);

#endif // LEXER_H
