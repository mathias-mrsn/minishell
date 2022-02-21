/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 11:04:37 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/21 15:34:53 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void
// 	handle_int(int signal)
// {
// 	if (s()->prog_state == HEREDOC_CHILD)
// 	{
// 		__putchar('\n', 1);
// 		exit(0);
// 	}
// 	if (s()->prog_state == FATHER)
// 		return ;
// 	if (s()->prog_state == HEREDOC_FATHER)
// 	{
// 		s()->g_exit_code = 130;
// 		s()->error = __TRUE;
// 		return ;
// 	}
// 	if (signal == SIGINT)
// 	{
// 		__putchar('\n', 1);
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 		s()->g_exit_code = 130;
// 	}
// }

// void
// 	handle_quit(int signal)
// {
// 	if (signal == SIGQUIT)
// 	{
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 		(void)signal;		
// 	}
// }

void
	__ctrl_d_exit__(void)
{
	uint32_t	exit_c;
	
	exit_c = s()->g_exit_code;
	__putstr("exit\n", 2);
	__clean_all();
	exit(exit_c);
}

void
	handle_int(siginfo_t *siginfo)
{
	if (s()->prog_state == OUT_OF_SHELL)
	{
		__putchar('\n', 1);
		exit(0);
	}
	if (siginfo->si_pid != 0)
	{
		__putchar('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		s()->g_exit_code = 130;
	}
	else
		wait(NULL);
}

void
	handle_quit(siginfo_t *siginfo)
{
	if (s()->prog_state == OUT_OF_SHELL)
	{
		__putchar('\n', 1);
		exit(0);
	}
	if (siginfo->si_pid != 0)
	{
		__putchar('\n', 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void
	signal_handler(int signal, siginfo_t *siginfo, void *data)
{
	(void)data;
	if (signal == SIGINT)
		handle_int(siginfo);
	if (signal == SIGQUIT && s()->prog_state == SHELL)
		handle_quit(siginfo);
}

void
	signal_gestion(t_mini *s)
{
	struct sigaction	sa;

	(void)s;
	__memset(&sa, 0, sizeof(struct sigaction));
	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	// sigaddset(&sa.sa_mask, SIGCHLD);
	sigaction(SIGINT, &sa, NULL);
	// if (s->prog_state == SHELL)
	// sigaction(SIGQUIT, &sa, NULL);
	// else if (s->prog_state == OUT_OF_SHELL)
	signal(SIGQUIT, SIG_IGN);
		
	// sigaction(SIGQUIT, &sa, NULL);	
}