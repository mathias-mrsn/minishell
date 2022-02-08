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
}

void	create_heredoc(t_command *cmd)
{
	int		fd;
	char	*line;

	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (fd < 0)
	{
		__puterr("Error while creating Heredoc!");
		//("Error while creating Heredoc!");
	}
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = __gnl(0);
		if (!__strncmp(cmd->limiter, line, __strlen(cmd->limiter)))
			break ;
		write(fd, line, __strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
	cmd->infile = open(".heredoc_tmp", O_RDONLY, 0644);
	if (cmd->infile < 0)
	{
			unlink(".heredoc_tmp");
			//("Infile error !");
	}
}

int	is_builtin(t_command *cmd)
{
	if (!__strncmp("cd", cmd->command, 3))
	{
		switch_io(cmd);
		exec_cd(cmd);
	}
	else if (!__strncmp("pwd", cmd->command, 4))
	{
		switch_io(cmd);
		exec_pwd();
	}
	else if (!__strncmp("echo", cmd->command, 5))
	{
		switch_io(cmd);
		exec_echo(cmd);
	}
	else if (!__strncmp("export", cmd->command, 7))
	{
		switch_io(cmd);
		exec_export(cmd);
	}
	else if (!__strncmp("unset", cmd->command, 6))
	{
		exec_unset(cmd);
	}
	else if (!__strncmp("exit", cmd->command, 5))
	{
		exec_exit(cmd);
	}
	else if (!__strncmp("env", cmd->command, 4))
	{
		switch_io(cmd);
		exec_env();
	}
	else
		return (0);
	return (1);
}

void	switch_io(t_command *cmd)
{	
	if (cmd->type == PIP)
    {
		write(2, "here\n", 5);
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
		tmp = __strjoin(*cmd_paths, "/");
		guess = __strjoin(tmp, args);
		free(tmp);
		if (access(guess, 0) == 0)
			return (guess);
		free(guess);
		cmd_paths++;
	}
	cmd->error = __strdup(args);
	return (NULL);
}

char	*__paths(char **envp)
{
	while (__strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

void	exec(t_command *cmd)
{
	char	*paths;
	char	**cmd_paths;
	int		i;

	switch_io(cmd);
	i = 0;
	paths = __paths(s()->env);
	cmd_paths = __split(paths, ':');
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
	execve(cmd->command, cmd->args, s()->env);
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

void	close_open_files(void)
{
	t_command *cmd;

	cmd = s()->cmd;
	while (cmd)
	{
		if (cmd->infile)
			close(cmd->infile);
		if (cmd->outfile)
			close(cmd->outfile);
		// if (cmd->limiter)
		unlink(".heredoc_tmp");
		cmd = cmd->next;
	}
}

void	exec_cmds(void)
{
	t_command	*cmd;

	cmd = s()->cmd;
	while (cmd)
	{
		if (!check_pipe(cmd))
			return ;
		if (!is_builtin(cmd))
		{
			cmd->child = fork();
			if (cmd->child == 0)
				exec(cmd);
		}
		close_prev_pipe(cmd);
		waitpid(cmd->child, NULL, 0);
		cmd = cmd->next;
	}
	close_open_files();
}


int
	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	t_mini	*mini;

	mini = s();
	if (__FAILURE == get_env(mini, env))
		return (EXIT_FAILURE); //free t_mini
	while(1)
	{
		__reset__(mini);
		print_prompt(mini);
		lexer(mini);
		if (__FALSE == mini->error)
			trimer(mini);
		if (__FALSE == mini->error)
			parsing(mini);
		if (__FALSE == mini->error)
		{
			exec_cmds();
			waitpid(-1, NULL, 0);
		}
		// print_cmd();
		__clean_all();
	}
	while(1);
	return (EXIT_SUCCESS);
}
