#include "minishell.h"

/* HELPING FUNCTIONS */

void
	print_s(t_mini *s)
{
	printf("MINISHELL\n");
	printf("\n\nEnv\n\n");
	for(int j = 0; s->env->values[j]; j++)
		printf("%s\n", s->env->values[j]);
	printf("\nprompt = [%s]\n\n", s->parse->prompt);
	for(int i = 0; s->parse->cmd[i]; i++)
	{
		printf("line %d : [%s]\n", i + 1, s->parse->cmd[i]);
		for (int p = 0; s->parse->cmd_splited[i][p].string; p++)
		{
			printf("[%s] ", s->parse->cmd_splited[i][p].string);
			printf("[%d] ", s->parse->cmd_splited[i][p].type);
		}
	}

}

/* REEL FUNCTIONS */

t_mini
	*s(void)
{
	static t_mini *s;

	if (!s)
	{
		s = __calloc(1, sizeof(t_mini));
		if (!s)
			return (NULL);
		s->parse = __calloc(1, sizeof(t_cmd));
		if (!s->parse)
			return (free(s), NULL);
		s->env = __calloc(1, sizeof(t_env));
		if (!s->env)
			return (free(s->parse), free(s), NULL);
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
	find_type(char *str, int id)
{
	if (id == 0)
		return (COMMAND);
	else
	{
		if (str[0] == '-')
			return (OPTIONS);
	}
	return (ARGUMENT);
}

int
	split_and_assign(t_mini *s, int index)
{
	char **save;
	uint32_t	i;

	i = 0;
	save = __split(s->parse->cmd[index], ' ');
	if (!save)
		return (__FAILURE);
	while(save[i])
		i++;
	s->parse->cmd_splited[index] = __calloc(i + 1, sizeof(t_detail));
	i = 0;
	while(save[i])
	{
		s->parse->cmd_splited[index][i].string = save[i];
		s->parse->cmd_splited[index][i].id = i;
		s->parse->cmd_splited[index][i].type = find_type(save[i], i);
		i++;
	}
	return (__SUCCESS);
}

int
	split_cmd(t_mini *s)
{
	s->parse->cmd = __split(s->parse->prompt, ';');
	if (NULL == s->parse->cmd)
		return (__FAILURE);
	return (__SUCCESS);
}

int
	__nbr_cmd__(char *str)
{
	uint32_t	nbr;
	uint64_t	index;

	index = 0;
	nbr = 1;
	if (!str)
		return (0);
	while (str[index])
	{
		if (str[index] == ';')
			nbr++;
		index++;
	}
	return (nbr);
}

int
	__is_correct_input__(t_mini *s)
{
	uint64_t	index;

	index = 0;
	while(s->parse->prompt[index])
	{
		if (0 == __isprint(s->parse->prompt[index]))
			return (__FAILURE);
		index++;
	}
	return (__SUCCESS);
}

char
	*__get_arg_cmd__(t_mini *s, int index)
{
	uint64_t i;

	i = 0;
	while(s->parse->cmd_splited[index])
	{
		if (s->parse->cmd_splited[index][i].type == OPTION)
			return (s->parse->cmd_splited[index][i].string);
		i++;
	}
	return (NULL);
}

char
	*__get_arg_cmd__(t_mini *s, int index)
{
	uint64_t i;

	i = 0;
	while(s->parse->cmd_splited[index])
	{
		if (s->parse->cmd_splited[index][i].type == ARGUMENT)
			return (s->parse->cmd_splited[index][i].string);
		i++;
	}
	return (NULL);
}

char
	*__get_cmd__(t_mini *s, int index)
{
	uint64_t i;

	i = 0;
	while(s->parse->cmd_splited[index])
	{
		if (s->parse->cmd_splited[index][i].type == COMMAND)
			return (s->parse->cmd_splited[index][i].string);
		i++;
	}
	return (NULL);
}

int
	pwd(t_mini *s, uint64_t index)
{
	char *actual_path;

	(void)s;
	(void)index;
	actual_path = getcwd(NULL, 2048);
	if (!actual_path)
		return (__FAILURE);
	printf("%s\n", actual_path);
	return (__SUCCESS);
}

int
	cd(t_mini *s, uint64_t index)
{
	char *arg;

	arg = __get_arg_cmd__(s, index);
	if (NULL == arg)
		return (__FAILURE); //No path
	chdir(arg);
	return (__SUCCESS);
}

int
	execution(t_mini *s)
{
	uint64_t index;

	index = 0;
	while (index < s->parse->nbr_cmd)
	{
		if (__strnstr(__get_cmd__(s, index), "pwd", INT_MAX))
			pwd(s, index);
		if (__strnstr(__get_cmd__(s, index), "cd", INT_MAX))
			cd(s, index);
		index++;
	}
	return (__SUCCESS);
}

int
	exe_cmd(t_mini *s)
{
	uint64_t	index;

	index = 0;
	if (__FAILURE == __is_correct_input__(s) || __FAILURE == split_cmd(s))
		return (__FAILURE);	
	s->parse->nbr_cmd = __nbr_cmd__(s->parse->prompt);
	s->parse->cmd_splited = __calloc(s->parse->nbr_cmd + 1, sizeof(t_detail *));
	s->parse->cmd_splited[s->parse->nbr_cmd] = NULL;
	if (NULL == s->parse->cmd_splited)
		return (__FAILURE);
	while(index < s->parse->nbr_cmd)
		if (__FAILURE == split_and_assign(s, index++))
			return (__FAILURE); 
	execution(s);
	return (__SUCCESS);
}

int
	get_prompt(t_mini *s)
{
	char *line;
	char *repo;
	char *prompt;

	repo = __get_last_repo__();
	if (NULL == repo)
	{
		perror("getcwd error\n");
		return (__FAILURE);
	}
	__memset(s->parse, 0, sizeof(t_cmd));
	prompt = __strcat(repo, " $> ");
	line = readline(prompt);
	free(prompt);
	add_history(line);
	s->parse->prompt = line;
	if (__FAILURE == exe_cmd(s))
		return (free(repo), free(line), __FAILURE);
	// print_s(s);
	return (free(repo), free(line), __SUCCESS);
}

int
	main(int ac, char **av, char **env)
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
