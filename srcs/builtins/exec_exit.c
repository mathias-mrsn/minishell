/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_exit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 12:02:44 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/17 08:46:20 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void    free_env_lst(void)
// {
//     t_env   **env_lst;
//     t_env   *current;
//     t_env   *tmp;

//     env_lst = s()->env_lst;
//     current = *env_lst;
//     while (current)
//     {
//         free(current->full);
//         free(current->key);
//         free(current->value);
//         tmp = current;
//         current = current->next;
//         free(tmp);
//     }
//     free(env_lst);
// }

static void
	__exit__(t_mini *s)
{
	const uint32_t	code = s->g_exit_code;

	__clean_all();
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
