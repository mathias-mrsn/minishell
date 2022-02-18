/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:52:48 by malouvar          #+#    #+#             */
/*   Updated: 2022/02/17 15:14:17 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_child(pid_t child)
{
	int	status;

	status = 0;
	waitpid(child, &status, 0);
	if (WIFEXITED(status))
		s()->g_exit_code = WEXITSTATUS(status);
	s()->prog_state = 0;
}

void
	__reset__(t_mini *s)
{
	s->lexer = NULL;
	s->cmd = NULL;
	s->error = 0;
	__clean(3);
	__clean(4);
}

t_boolean
	minishell(t_mini *s)
{
	while (1)
	{
		__reset__(s);
		print_prompt(s);
		if (s->prompt == NULL)
			__ctrl_d_exit__();
		lexer(s);
		trimer(s);
		parsing(s);
		if (__FALSE == s->error)
		{
			exec_cmds();
			waitpid(-1, NULL, 0);
		}
	}
	return (__SUCCESS);
}

int
	main(int ac, char **av, char **env)
{
	t_mini	*mini;

	(void)ac;
	(void)av;
	(void)env;
	mini = s();
	if (1 != ac)
		return (__puterr(TOO_MANY_ARG_ERR), EXIT_FAILURE);
	else if (__FAILURE == get_env(mini, env))
		return (EXIT_FAILURE);
	signal(SIGQUIT, handle_quit);
	signal(SIGINT, handle_int);
	minishell(mini);
	return (EXIT_SUCCESS);
}
