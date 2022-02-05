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
		{
			trimer(mini);
			parsing(mini);
			exec(mini);
		}
		// print_cmd();
		__clean_all();
	}
	while(1);
	return (EXIT_SUCCESS);
}
