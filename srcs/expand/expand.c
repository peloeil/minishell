/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 17:55:00 by sota              #+#    #+#             */
/*   Updated: 2025/05/04 16:47:58 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <minishell/expand.h>
#include <libft/ft_ctype.h>
#include <libft/ft_string.h>
#include <stdlib.h>

static int	dollar_as_prefix(const char *str, size_t index)
{
	if (str[index] != '$')
		return (0);
	if (str[index + 1] == '\0')
		return (0);
	if (str[index + 1] == ' ' || str[index + 1] == '\t')
		return (0);
	return (1);
}

static char	*read_variable_key(char *str, size_t index)
{
	t_string	key;
	char		c;

	if (ft_isdigit(str[++index]))
		return (NULL);
	if (ft_str_new(&key) == -1)
		return (NULL);
	while (1)
	{
		c = str[index++];
		if (c == '_' || ft_isalnum(c))
		{
			if (ft_str_push(&key, c) == -1)
				return (NULL);
		}
		else
			break ;
	}
	return (key.str);
}

static char	*read_variable_value(char *key, const t_envp *envp)
{
	char	*value;

	if (key == NULL)
		return (NULL);
	value = ft_getenv(key, envp);
	if (value == NULL)
		value = "";
	return (ft_strdup(value));
}

static t_envp	*read_variable(char *str, size_t index, const t_envp *envp)
{
	t_envp	*key_value;

	key_value = (t_envp *)malloc(sizeof(t_envp));
	if (key_value == NULL)
		return (NULL);
	key_value->key = read_variable_key(str, index);
	if (key_value->key == NULL)
	{
		free(key_value);
		return (NULL);
	}
	key_value->value = read_variable_value(key_value->key, envp);
	if (key_value->value == NULL)
	{
		free(key_value->key);
		free(key_value);
		return (NULL);
	}
	return (key_value);
}

static int	expand_arg(t_arg_list **arg, const t_envp *envp)
{
	char		*str;
	t_envp		*key_value;
	t_string	new_str;
	size_t		index;
	int			single_quoted;

	ft_str_new(&new_str);
	str = (char *)((*arg)->content);
	index = 0;
	single_quoted = 0;
	while (str[index] != '\0')
	{
		if (!single_quoted && dollar_as_prefix(str, index))
		{
			key_value = read_variable(str, index, (const t_envp *)envp);
			if (key_value == NULL) // start with numeric character
			{
				free(new_str.str);
				return (-1);
			}
			ft_str_push_str(&new_str, key_value->value);
			free(key_value->value);
			index += 1 + ft_strlen(key_value->key);
			free(key_value->key);
			free(key_value);
		}
		else
		{
			ft_str_push(&new_str, str[index]);
			single_quoted ^= (str[index] == '\'');
			index++;
		}
	}
	free(str);
	(*arg)->content = new_str.str;
	return (0);
}

static int	expand_args(t_arg_list **args, const t_envp *envp)
{
	t_arg_list	*cur;

	cur = *args;
	while (1)
	{
		if (expand_arg(&cur, envp) == -1)
			return (-1);
		cur = cur->next;
		if (cur == *args)
			break ;
	}
	return (0);
}

int	expand_variables(t_ast_node *ast, const t_envp *envp)
{
	if (ast->left == NULL)
		return (expand_args(&ast->args, envp));
	if (expand_variables(ast->left, envp) == -1)
		return (-1);
	if (expand_variables(ast->right, envp) == -1)
		return (-1);
	return (expand_args(&ast->args, envp));
}
