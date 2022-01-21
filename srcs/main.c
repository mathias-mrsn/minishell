#include "minishell.h"

/* HELPING FUNCTIONS */

// void
// 	print(t_mini *s)
// {
// 	printf("%s\n", s->whole_cmd);
// }

/*
**	REEL FUNCTIONS
*/

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
	(void)env;
	t_mini	*mini;

	mini = s();
	// if (__FAILURE == get_env(mini, env))
	// 	return (EXIT_FAILURE); //free t_mini
	while(1)
	{
		__reset__(mini);
		print_prompt(mini);
		lexer(mini);
		// print(mini);
		// __clean();
	}
	while(1);
	return (EXIT_SUCCESS);
}
