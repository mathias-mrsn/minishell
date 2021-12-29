#include "minishell.h"

/* HELPING FUNCTIONS */

void	print_s(t_mini *s)
{
	printf("MINISHELL\n");
	printf("\npromtp = [%s]\n\n", s->cmd->prompt);
	for(int i = 0; s->cmd->cmd[i]; i++)
		printf("line %d : [%s]\n", i + 1, s->cmd->cmd[i]);

}

/* REEL FUNCTIONS */

t_mini *s(void)
{
	static t_mini *s;

	if (!s)
	{
		s = __calloc(1, sizeof(t_mini));
		if (!s)
			return (NULL);
		s->cmd = __calloc(1, sizeof(t_cmd));
		if (!s->cmd)
			return (free(s), NULL);
	}
	return (s);
}

void		handle(int signal)
{
	(void)signal;
	get_prompt(s());
}

void	get_prompt(t_mini *s)
{
	char *line;

	signal(SIGINT, handle);
	line = readline("minishell $> ");
	add_history(line);
	s->cmd->prompt = line;
	s->cmd->cmd = __split(line, ';');
	s->nbr_cmd += 1;
}

void	new_line(int signal)
{
	(void)signal;
	printf("Ctrl+C\n");
	rl_on_new_line();
}

int main()
{
	t_mini *mini = s();
	struct sigaction sa;

	__memset(&sa, 0, sizeof(struct sigaction));
	while(1)
	{
		__memset(mini->cmd, 0, sizeof(t_cmd));
		get_prompt(mini);
		print_s(mini);
	}
}
