/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 01:03:28 by sota              #+#    #+#             */
/*   Updated: 2025/05/11 01:12:52 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell/minishell.h>
#include <minishell/execute.h>
#include <libft/ft_stdio.h>

int	update_exit_status(t_exit_status status, t_envp *envp)
{
	char	*argv[3];
	char	str[20];

	if (ft_sprintf(str, "?=%d", (int)status) == -1)
		return (-1);
	argv[0] = "export";
	argv[1] = str;
	argv[2] = NULL;
	if (export(0, argv, envp) == -1)
		return (-1);
	return (0);
}
