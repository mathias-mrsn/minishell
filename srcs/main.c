#include "minishell.h"

/* HELPING FUNCTIONS */

// void
// 	print_s(t_mini *s)
// {
// 	printf("MINISHELL\n");
// 	printf("\n\nEnv\n\n");
// 	for(int j = 0; s->env->values[j]; j++)
// 		printf("%s\n", s->env->values[j]);
// 	printf("\nprompt = [%s]\n\n", s->parse->prompt);
// 	for(int i = 0; s->parse->cmd[i]; i++)
// 	{
// 		printf("line %d : [%s]\n", i + 1, s->parse->cmd[i]);
// 		for (int p = 0; s->parse->cmd_splited[i][p].string; p++)
// 		{
// 			printf("[%s] ", s->parse->cmd_splited[i][p].string);
// 			printf("[%d] ", s->parse->cmd_splited[i][p].type);
// 		}
// 	}

// }

/* REEL FUNCTIONS */



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
		mini->prompt = readline("$>");
		add_history(mini->prompt);
		if (__FAILURE == trim_quotes(mini))
			return (printf("ERROR"), EXIT_FAILURE); 
		printf("new line = %s\n", mini->whole_cmd);
	}
	return (EXIT_SUCCESS);
}
