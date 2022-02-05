/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 16:56:13 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/05 17:21:40 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	__exit__(t_mini *s)
{
	const uint8_t	code = s->g_exit_code;
	
	__clean_all();
	clear_history();
	free(s);
	exit(code);
}

static void
	__exit_with_value__(t_mini *s, char **strs, size_t strslen)
{
	if (strslen == 1)
		s->g_exit_code = __atoi(strs[1]);
	else
	{
		s->g_exit_code = 1;
		__putstr(PROGRAM_NAME, STDERR_FILENO);
		__putstr(": exit: ", STDERR_FILENO);
		__putstr("too many arguments\n", STDERR_FILENO);
	}
	if (strslen == 1)
		__exit__(s);
}

t_boolean
	builtins_exit(t_mini *s, t_command *cmd)
{
	const size_t strslen = __strslen(cmd->args) - 1;

	if (strslen == 0)
		return (__putstr("exit\n", STDERR_FILENO), __exit__(s), __SUCCESS);
	else if (strslen && __TRUE == __str_is(cmd->args[1], __IS_DIGIT))
		return (__putstr("exit\n", STDERR_FILENO),
			__exit_with_value__(s, cmd->args, strslen), __SUCCESS);
	else
	{
		s->g_exit_code = 255;
		__putstr("exit\n", STDERR_FILENO);
		__putstr(PROGRAM_NAME, STDERR_FILENO);
		__putstr(": exit: ", STDERR_FILENO);
		__putstr(cmd->args[1], STDERR_FILENO);
		__putstr(": numeric argument required\n", STDERR_FILENO);
		__exit__(s);
	}		
	return (__SUCCESS);
}