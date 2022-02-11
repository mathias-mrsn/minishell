/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 14:39:07 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/10 19:31:17 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
 	__is_builtins__(t_command *cmd)
 {
 	char	*str;
 	int		idx;
 	const char	*commands[NBR_BUILDINS] = {"unset",
 		"exit", "env", "export", "cd", "pwd", "echo"};

 	idx = 0;
 	str = cmd->command;
 	while(idx < NBR_BUILDINS)
 	{
 		if (__strcmp(str, commands[idx]) == 0)
 			return (idx + 1);
 		idx++;
 	}
 	return (__FALSE);
 }

t_boolean
 	exec_builtins(t_command *cmd)
 {

 	static void	(*f[NBR_BUILDINS])() = {exec_unset, exec_exit, exec_env, exec_export,
		exec_cd, exec_pwd, exec_echo};
 	const int		i = __is_builtins__(cmd);

	if (0 == i)
		return (__FAILURE);
	if (i > 2)
		switch_io(cmd);
 	f[i - 1](cmd);
 	return (__SUCCESS);
 }