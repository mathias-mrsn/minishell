/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 14:36:01 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/22 17:38:54 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*__cmd(char **cmd_paths, char *args, t_command *cmd)
{
	char	*guess;
	char	*tmp;

	if (access(args, 0) == 0)
		return (args);
	while (*cmd_paths)
	{
		tmp = __mstrjoin(*cmd_paths, "/", __DONT_STOCK_MEM);
		guess = __mstrjoin(tmp, args, __DONT_STOCK_MEM);
		free(tmp);
		if (access(guess, 0) == 0)
			return (guess);
		free(guess);
		cmd_paths++;
	}
	cmd->error = __strdup(args);
	return (NULL);
}

char	*__get_path__(t_mini *s)
{
	t_env	*tmp;

	tmp = NULL;
	tmp = (*(s->env_lst));
	while (tmp)
	{
		if (0 == __strcmp(tmp->key, "PATH"))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

void
	__execve__(char *command, char **args)
{
	char	**strs;

	strs = __env_to_strs__(s());
	execve(command, args, strs);
}

void	exec(t_command *cmd)
{
	char	*paths;
	char	**cmd_paths;
	int		i;

	switch_io(cmd);
	i = 0;
	signal(SIGQUIT, SIG_DFL);
	paths = __get_path__(s());
	if (!paths)
		path_not_set(cmd);
	cmd_paths = __msplit(paths, ':', __DONT_STOCK_MEM);
	cmd->command = __cmd(cmd_paths, cmd->command, cmd);
	while (cmd_paths[i])
		free(cmd_paths[i++]);
	if (!cmd->command)
	{
		if (__strchr(cmd->error, '/'))
			write(2, "minishell:  no such file or directory: ", 39);
		else
			write(2, "minishell:  command not found: ", 31);
		write(2, cmd->error, __strlen(cmd->error));
		write(2, "\n", 1);
		exit (127);
	}
	__execve__(cmd->command, cmd->args);
}

void	exec_cmds(void)
{
	t_command	*cmd;
	int			stdin_copy;
	int			stdout_copy;

	stdin_copy = dup(0);
	stdout_copy = dup(1);
	cmd = s()->cmd;
	while (cmd && cmd->command)
	{
		if (!check_pipe(cmd))
			return ;
		if (__FAILURE == exec_builtins(cmd))
		{
			cmd->child = fork();
			if (cmd->child == 0)
				exec(cmd);
		}
		close_prev_pipe(cmd);
		if (cmd->child)
			wait_child(cmd->child);
		cmd = cmd->next;
	}
	close_open_files(stdin_copy, stdout_copy);
}
