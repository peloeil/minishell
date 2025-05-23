/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sota <sota@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 01:03:28 by sota              #+#    #+#             */
/*   Updated: 2025/05/15 04:05:01 by sota             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft/ft_stdio.h>
#include <libft/ft_stdlib.h>
#include <minishell/execute.h>
#include <minishell/minishell.h>

// ここの関数が常に export に ? を入れている
// ここでしたいことは？の更新
// 更新用に関数に置き換える
int	update_exit_status(t_exit_status status, t_envp *envp)
{
	char	*str_status;

	// char	*argv[3];
	// char	str[20];
	// if (ft_sprintf(str, "?=%d", (int)status) == -1)
	// 	return (-1);
	// argv[0] = "export";
	// argv[1] = str;
	// argv[2] = NULL;
	str_status = ft_itoa(status);
	add_envp_with_flag("?", str_status, envp, FLAG_SPECIAL);
	// if (export(0, argv, &envp) == -1)
	// 	return (-1);
	return (status);
}
