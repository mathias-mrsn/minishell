/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathias <mathias@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 11:04:37 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/18 15:09:42 by mathias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	handle_int(int signal)
{
	if (s()->prog_state == HEREDOC_CHILD)
	{
		__putchar('\n', 1);
		exit(0);
	}
	if (s()->prog_state == FATHER)
		return ;
	if (s()->prog_state == HEREDOC_FATHER)
	{
		s()->g_exit_code = 130;
		s()->error = __TRUE;
		return ;
	}
	if (signal == SIGINT)
	{
		__putchar('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		s()->g_exit_code = 130;
	}
}

void
	handle_quit(int signal)
{
	if (signal == SIGQUIT && s()->prog_state == FATHER)
	{
		__putstr("Quit (core dumped)\n", 2);
		s()->g_exit_code = 131;
	}
}

void
	__ctrl_d_exit__(void)
{
	__putstr("exit\n", 2);
	__clean_all();
	exit(EXIT_SUCCESS);
}
