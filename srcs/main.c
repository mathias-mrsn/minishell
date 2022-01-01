#include "minishell.h"

/* HELPING FUNCTIONS */

void	print_s(t_mini *s)
{
	printf("MINISHELL\n");
	printf("\n\nEnv\n\n");
	for(int j = 0; s->env->values[j]; j++)
		printf("%s\n", s->env->values[j]);
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
		s->env = __calloc(1, sizeof(t_env));
		if (!s->env)
			return (free(s->cmd), free(s), NULL);
	}
	return (s);
}

int
	get_env(t_mini *s, char **env)
{
	uint32_t	size;

	size = 0;
	while(NULL != env[size])
		size++;
	s->env->values = __calloc(size + 1, sizeof(char *));
	if (NULL == s->env->values)
		return (__FAILURE); // free s, cmd, env
	while(size--)
		s->env->values[size] = env[size];
	return (__SUCCESS);
}

char
	*__get_last_repo__(void)
{
	char *actual_path;
	int	size;
	int total;

	total = 0;
	actual_path = getcwd(NULL, 2048);
	if (!actual_path)
		return (NULL);
	size = ft_strlen(actual_path);
	while(size-- && ++total)
		if (actual_path[size] == '/')
			break;
	return (__substr(actual_path, size + 1, total));
}

int
	get_prompt(t_mini *s)
{
	char *line;
	char *repo;

	repo = __get_last_repo__();
	if (NULL == repo)
	{
		perror("getcwd error\n");
		return (__FAILURE);
	}
	__memset(s->cmd, 0, sizeof(t_cmd));
	printf("%s%s%s $> %s", __BCYAN, repo, __BGREEN, __RESET);
	line = readline(NULL);
	add_history(line);
	s->cmd->prompt = line;
	s->cmd->cmd = __split(line, ';');
	s->nbr_cmd += 1;
	print_s(s);
	return (free(repo), free(line), __SUCCESS);
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	t_mini *mini = s();

	if (__FAILURE == get_env(mini, env))
		return (EXIT_FAILURE); //free t_mini
	while(1)
	{
		if (__FAILURE == get_prompt(mini))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
