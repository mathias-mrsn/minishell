#include "minishell.h"

/* HELPING FUNCTIONS */

void
	print(t_mini *s)
{
	for(uint64_t i = 0; i < s->nbr_cmd; i++)
	{
		printf("id : %llu ==> [%s]\n", i, s->cmd[i].full_cmd);
		for (uint64_t j = 0; j < s->cmd[i].nbr_pip; j++)
		{
			printf("\t\tid : %llu ==> [%s]\n", j, s->cmd[i].pip[j].full);
			printf("\t\t\t\tcommand id : %llu ==> [%s]\n", j, s->cmd[i].pip[j].command);
			printf("\t\t\t\t\t\toption id : %llu ==> [%s]\n", j, s->cmd[i].pip[j].option);
		}
	}
}

/* REEL FUNCTIONS */

void
	__reset__(t_mini *s)
{
	s->nbr_cmd = 0;
}

int
	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_mini	*mini;

	mini = s();
	if (__FAILURE == get_env(mini, env))
		return (EXIT_FAILURE); //free t_mini
	// if (__FAILURE == trim_quotes(mini))
	// 	return (printf("ERROR"), EXIT_FAILURE); 
	while(1)
	{
		__reset__(mini);
		mini->prompt = readline("$>");
		add_history(mini->prompt);
		trim_quotes(mini);
		printf("new line = %s\n", mini->whole_cmd);
		split_shell(mini);
		parse_hub(mini);
		print(mini);
		// __clean();
	}
	while(1);
	return (EXIT_SUCCESS);
}
