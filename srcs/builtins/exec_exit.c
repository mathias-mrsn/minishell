/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 12:02:44 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/21 15:35:04 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	__exit__(t_mini *s)
{
	const uint32_t	code = s->g_exit_code;

	// __print_memory();
	__clean_all();
	// __print_memory();
	clear_history();
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

void
	exec_exit(t_command *cmd)
{
	const size_t	strslen = __strslen(cmd->args) - 1;

	if (strslen == 0)
	{
		__putstr("exit\n", STDERR_FILENO);
		__exit__(s());
	}
	else if (strslen && __TRUE == __str_is(cmd->args[1], __IS_DIGIT))
	{
		__putstr("exit\n", STDERR_FILENO);
		__exit_with_value__(s(), cmd->args, strslen);
	}
	else
	{
		s()->g_exit_code = 255;
		__putstr("exit\n", STDERR_FILENO);
		__putstr(PROGRAM_NAME, STDERR_FILENO);
		__putstr(": exit: ", STDERR_FILENO);
		__putstr(cmd->args[1], STDERR_FILENO);
		__putstr(": numeric argument required\n", STDERR_FILENO);
		__exit__(s());
	}
}
