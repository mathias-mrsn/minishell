/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathias <mathias@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 14:39:07 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/18 15:18:08 by mathias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int
	__is_builtins__(t_command *cmd)
{
	char		*str;
	int			idx;
	const char	*commands[NBR_BUILDINS] = {"unset",
		"exit", "cd", "export", "env", "pwd", "echo"};

	idx = 0;
	str = cmd->command;
	while (idx < NBR_BUILDINS)
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
	static void		(*f[NBR_BUILDINS])() = {exec_unset, exec_exit, exec_cd,
		exec_export, exec_env, exec_pwd, exec_echo};
	const int		i = __is_builtins__(cmd);

	if (0 == i)
		return (__FAILURE);
	if (i > 4 || (i == 4 && !cmd->args[1]))
	{
		cmd->child = fork();
		if (cmd->child == 0)
		{
			switch_io(cmd);
			f[i - 1](cmd);
			__clean_all();
			exit(0);
		}
		else
			wait_child(cmd->child);
	}
	else
		f[i - 1](cmd);
	return (__SUCCESS);
}
