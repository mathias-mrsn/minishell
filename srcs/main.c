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

void	get_prompt(t_mini *s)
{
	char *line;

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
	t_mini mini;

	__memset(&mini, 0, sizeof(t_mini));
	mini.cmd = malloc(sizeof(t_cmd));
	if (mini.cmd == NULL)
		return (1);
	
	while(1)
	{
		signal(SIGINT, new_line);
		__memset(mini.cmd, 0, sizeof(t_cmd));
		get_prompt(&mini);
		print_s(&mini);
	}
}
