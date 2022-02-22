/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:52:48 by malouvar          #+#    #+#             */
/*   Updated: 2022/02/22 17:53:48 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	__reset__(t_mini *s)
{
	s->lexer = NULL;
	s->cmd = NULL;
	s->error = 0;
	__clean(3);
	__clean(4);
}

static t_boolean
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

static t_boolean
	exec_fd(t_mini *s, int fd)
{
	char	*str;

	str = __gnl(fd);
	while (str)
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
	return (__SUCCESS);
}

static t_boolean
	exec_arg(t_mini *s, char **av)
{
	int		fd;

	if (0 == __file_exist(av[1]))
		return (__file_dont_exist__(s, av[1]), s->g_exit_code = 127, __FAILURE);
	fd = open(av[1], O_RDONLY);
	exec_fd(s, fd);
	return (__SUCCESS);
}

int
	main(int ac, char **av, char **env)
{
	t_mini		*mini;
	uint32_t	exit_c;

	mini = s();
	if (__FAILURE == get_env(mini, env))
		return (EXIT_FAILURE);
	signal_gestion(mini);
	if (ac > 1)
		exec_arg(mini, av);
	else if (isatty(__STDIN) == 0)
		exec_fd(mini, __STDIN);
	else
		minishell(mini);
	exit_c = mini->g_exit_code;
	__clean_all();
	return (exit_c);
}
