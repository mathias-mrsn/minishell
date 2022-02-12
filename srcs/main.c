#include "minishell.h"

/* HELPING FUNCTIONS */

void
	print_cmd(void)
{
	t_command *cmd = s()->cmd;
	int i = 0;

	while (cmd)
	{
		i = 0;
		while(cmd->args && cmd->args[i])
			printf("%s", cmd->args[i++]);
		cmd = cmd->next;
	}
}

/*
**	REEL FUNCTIONS
*/

void
	__reset__(t_mini *s)
{
	(void)s;
	s->lexer = NULL;
	s->cmd = NULL;
	s->error = 0;
	__clean(3);
	__clean(4);
}


void	switch_io(t_command *cmd)
{	
	if (cmd->type == PIP)
    {
        dup2(cmd->tube[1], 1);
        close(cmd->tube[0]);
    }
    if (cmd->prev && cmd->prev->type == PIP)
    {
        dup2(cmd->prev->tube[0], 0);
        close(cmd->prev->tube[1]);
    }
	if (cmd->outfile)
	{
		dup2(cmd->outfile, 1);
	}
	if (cmd->infile)
		dup2(cmd->infile, 0);
}

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

static void
	__execve__(char *command, char **args)
{
	char	**strs;

	strs = __env_to_strs__(s());
	execve(command, args, strs);
	__strsfree(strs);
}

void	exec(t_command *cmd)
{
	char	*paths;
	char	**cmd_paths;
	int		i;

	switch_io(cmd);
	i = 0;
	paths = __get_path__(s());
	cmd_paths = __msplit(paths, ':', __DONT_STOCK_MEM);
	cmd->command = __cmd(cmd_paths, cmd->command, cmd);
	while(cmd_paths[i])
	{
		free(cmd_paths[i]);
		i++;
	}
	if (!cmd->command)
	{
		if (__strchr(cmd->error, '/'))
			write(2, "minishell:  no such file or directory: ", 39);
		else
			write(2, "minishell:  command not found: ", 31);
		write(2, cmd->error, __strlen(cmd->error));
		write(2, "\n", 1);
		return ;
	}
	__execve__(cmd->command, cmd->args);
}

int	check_pipe(t_command *cmd)
{
	if (cmd->type == PIP)
	{
		if (pipe(cmd->tube) < 0)
			return (0);
		else
			return (1);
	}
	return (1);
}

void	close_prev_pipe(t_command *cmd)
{
	if (cmd->prev && cmd->prev->type == PIP)
	{
		close(cmd->prev->tube[0]);
		close(cmd->prev->tube[1]);
	}
}

void	close_open_files(int stdin_copy, int stdout_copy)
{
	t_command *cmd;

	cmd = s()->cmd;
	while (cmd)
	{
		if (cmd->infile)
		{
			close(cmd->infile);
			dup2(stdin_copy, 0);
			close(stdin_copy);

		}
		if (cmd->outfile)
		{
			close(cmd->outfile);
			dup2(stdout_copy, 1);
			close(stdout_copy);
		}
		unlink(".heredoc_tmp");
		cmd = cmd->next;
	}
}

void	exec_cmds(void)
{
	t_command	*cmd;
	int stdin_copy = dup(0);
	int stdout_copy = dup(1);

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
			waitpid(cmd->child, NULL, 0);
		cmd = cmd->next;
	}
	close_open_files(stdin_copy, stdout_copy);
}



t_boolean
	minishell(t_mini *s)
{
	while(1)
	{
		__reset__(s);
		print_prompt(s);
		if (s->prompt == NULL)
			__ctrl_d_exit__(s);
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
	(void)ac;
	(void)av;
	(void)env;
	t_mini	*mini;

	mini = s();
	if (1 != ac)
		return (__puterr(TOO_MANY_ARG_ERR), EXIT_FAILURE);
	else if (__FAILURE == get_env(mini, env))
		return (EXIT_FAILURE); //free t_mini
	signal(SIGQUIT, handle_quit);
	signal(SIGINT, handle_int);
	minishell(mini);
	return (EXIT_SUCCESS);
}
