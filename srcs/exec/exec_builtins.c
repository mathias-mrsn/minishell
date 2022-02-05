/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 14:39:07 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/05 15:37:52 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

# define NBR_BUILDINS	7

int
	__is_builtins__(t_command *cmd)
{
	char	*str;
	int		idx;
	const char	*commands[NBR_BUILDINS] = {"echo",
		"pwd", "cd", "export", "env", "unset", "exit"};

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
	exec_builtins(t_mini *s, t_command *cmd)
{
	static t_boolean	(*f[1])() = {builtins_echo}; //changer par NBR_BUILTINS
	const int		i = __is_builtins__(cmd);
	
	f[i - 1](s, cmd);
	return (__SUCCESS);
}

