/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:52:48 by malouvar          #+#    #+#             */
/*   Updated: 2022/02/21 15:52:43 by mamaurai         ###   ########.fr       */
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
	if (WIFSIGNALED(status) && WCOREDUMP(status))
	{
		__putstr("Quit (core dumped)\n", 2);
		s()->g_exit_code = 131;
	}
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

t_boolean
	exec_atty(t_mini *s)
{
	char	*str;
	
	str = __gnl(__STDIN);
	while(str)
	{
		s->prompt = str;
		__reset__(s);
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
		str = __gnl(__STDIN);
	}
	return (__SUCCESS);
}

t_boolean
	exec_arg(t_mini *s, char **av)
{
	int 	fd;
	char	*str;

	if (0 == __file_exist(av[1]))
		return (__file_dont_exist__(s, av[1]), s->g_exit_code = 127, __FAILURE);
	fd = open(av[1], O_RDONLY);
	printf("%s\n", av[1]);
	str = __gnl(fd);
	while(str)
	{
		s->prompt = str;
		__reset__(s);
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
		str = __gnl(fd);
	}
	return (fd);
	
}

int
	main(int ac, char **av, char **env)
{
	t_mini	*mini;

	mini = s();
	if (__FAILURE == get_env(mini, env))
		return (EXIT_FAILURE);
	// signal(SIGQUIT, handle_quit);
	// signal(SIGINT, handle_int);
	signal_gestion(mini);
	if (ac > 1)
		exec_arg(mini, av);
	else if (isatty(__STDIN) == 0)
		exec_atty(mini);
	else
		minishell(mini);
	__clean_all();
	return (EXIT_SUCCESS);
}
