/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 11:04:37 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/12 11:05:02 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void
	handle_int(int signal)
{
	if (s()->prog_state == HEREDOC_CHILD)
	{
		__putchar('\n', 1);
		exit(130);
	}
	if (s()->prog_state == HEREDOC_FATHER)
	{
		__putchar('\n', 1);
		s()->g_exit_code = 130;
		return;
	}
	if (signal == SIGINT)
	{
		__putchar('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		s()->g_exit_code = 130;
	}
	s()->error = __TRUE;
}

void
	handle_quit(int signal)
{
	if (signal == SIGQUIT && s()->prog_state == 0)
	{
		__putstr("Quit (core dumped)\n", 2);
		s()->g_exit_code = 131;
	}
}

void
	__ctrl_d_exit__(t_mini *s)
{
	__putstr("exit\n", 2);
	__clean_all();
	//free env
	free(s);
	exit(EXIT_SUCCESS);
}

