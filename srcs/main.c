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

t_mini
	*s(void)
{
	static t_mini *s;

	if (!s)
	{
		s = __malloc(sizeof(t_mini) * 1);
		if (!s)
			return (NULL);
	}
	return (s);
}

char
	*__get_env_value__(t_mini *s, char *tofind)
{
	uint64_t	index;

	index = 0;
	if (!tofind)
		return (NULL);
	while (NULL != s->env[index])
	{
		if (__SUCCESS == __str_start_with(s->env[index], tofind))
			return (__strnstr(s->env[index], "=", SIZE_T_MAX) + 1);
		index++;
	}
	return (NULL);
}

uint8_t
	get_env(t_mini *s, char **env)
{
	uint64_t	size;

	size = 0;
	while(NULL != env[size])
		size++;
	s->env = __malloc((size + 1) * sizeof(char *));
	if (NULL == s->env)
		return (__FAILURE); // free s, cmd, env
	s->env[size] = NULL;
	while(size--)
		s->env[size] = env[size];
	s->path = __get_env_value__(s, "PATH");
	return (__SUCCESS);
}

uint8_t
	__quotes_are_right__(t_mini *s)
{
	uint64_t	index;
	uint64_t	simple_quote;
	uint64_t	double_quote;

	index = 0;
	simple_quote = 0;
	double_quote  = 0;
	while (s->prompt[index])
	{
		if (s->prompt[index] == '\'')
			simple_quote += 1;
		else if (s->prompt[index] == '\"')
			double_quote += 1;
		index += 1;
	}
	if (1 == (simple_quote % 2) || 1 == (double_quote % 2))
		return (__FAILURE);
	return (__SUCCESS);
}

uint64_t
	__variable_name_length__(char *str)
{
	uint64_t	index;

	index = 1;
	while (str[index] && __FAILURE == __is_charset(str[index], " \'\"$"))
		index += 1;
	return (index - 1);
}

char
	*__catch_variable_name__(char *str)
{
	uint64_t	index;
	char		*res;

	res = (char *)__malloc(sizeof(char) * (__variable_name_length__(str) + 2));
	if (NULL == res)
		return (printf("catch 1\n"), NULL);
	index = 0;
	while (++index && str[index] && __FAILURE == __is_charset(str[index], " \'\"$"))
		res[index -  1] = str[index];
	res[index - 1] = '\0';
	return (res);
}

uint8_t
	replace_value(t_mini *s, uint64_t *n, uint64_t *p)
{
	char		*str;
	char		*name;
	uint64_t	i;

	name = NULL;
	if (0 == __variable_name_length__(s->prompt + (*p)))
		str = __strdup("$");
	else
	{
		name = __catch_variable_name__(s->prompt + (*p));
		if (!name)
			return (printf("replace 1\n"), __FAILURE);
		str = __strdup(__get_env_value__(s, name));
	}
	i = 0;
	while (str && str[i])
	{
		s->whole_cmd[(*n)] = str[i];
		i++;
		(*n)++; 
	}
	(*p)++;
	while (s->prompt[(*p)] && __is_charset(s->prompt[(*p)], "  \'\"$"))
		(*p)++;
	return (free(name), free(str), __SUCCESS);
}

int64_t
	__value_lenght__(t_mini *s, uint64_t i)
{
	char *name;
	char *value;
	int64_t	size;

	printf("%c\n", s->prompt[i + 1]);
	if (__SUCCESS == __is_charset(s->prompt[i + 1], " \'\"$") || !s->prompt[i + 1])
		return (1);
	name = __catch_variable_name__(s->prompt + i);
	if (!name)
		return (__ERROR);
	value = (char *)__get_env_value__(s, name);
	size = __strlen(value);
	printf("[%llu]\n", size);
	return (size);
}

uint64_t
	new_line_size(t_mini *s)
{
	uint64_t	index;
	uint64_t	size;
	uint8_t		sw;

	size = 0;
	index = 0;
	sw = 0;
	while(s->prompt[index])
	{
		if (s->prompt[index] == '\'' && 0 == sw)
			sw = 1;
		else if (s->prompt[index] == '\'' && 1 == sw)
			sw = 0;
		if (!sw && s->prompt[index] == '$')
		{
			printf("$ has been found\n");
			size += __value_lenght__(s, index);
			printf("size = %llu\n", size);
			index++;
			while(s->prompt[index] && __FAILURE == __is_charset(s->prompt[index], " \'\"$"))
				index++;
		}
		else
		{
			index++;
			size++;
		}
	}
	return (size);
}

uint8_t
	replace_env_values(t_mini *s)
{
	uint64_t	index_p;
	uint64_t	index_n;
	uint8_t		sw;

	sw = 0;
	index_n = 0;
	index_p = 0;
	s->whole_cmd = (char *)__malloc(sizeof(char) * (new_line_size(s) + 1));
	if (NULL == s->whole_cmd)
		return (__FAILURE);
	while (s->prompt[index_p])
	{
		if (s->prompt[index_p] == '\'' && 0 == sw)
			sw = 1;
		else if (s->prompt[index_p] == '\'' && 1 == sw)
			sw = 0;
		if (!sw && s->prompt[index_p] == '$')
		{
			if (__FAILURE == replace_value(s, &index_n, &index_p))
				return (__FAILURE);
		}
		else
		{
			s->whole_cmd[index_n] = s->prompt[index_p];
			index_n += 1;
			index_p += 1;
		}
	}
	s->whole_cmd[index_n] = 0;
	return (__SUCCESS);
}

uint8_t
	trim_quotes(t_mini *s)
{
	if (__FAILURE == __quotes_are_right__(s))
		return (__FAILURE); //print error message
	if (__FAILURE == replace_env_values(s))
		return (__FAILURE);
	return (__SUCCESS);
	
}


// int
// 	get_prompt(t_mini *s)
// {
// 	char *line;
// 	char *repo;
// 	char *prompt;

// 	repo = __get_last_repo__();
// 	if (NULL == repo)
// 	{
// 		perror("getcwd error\n");
// 		return (__FAILURE);
// 	}
// 	prompt = __strcat(repo, " $> ");
// 	line = readline(prompt);
// 	free(prompt);
// 	add_history(line);
// 	s->prompt = line;
// 	if (__FAILURE == exe_cmd(s))
// 		return (free(repo), free(line), __FAILURE);
// 	// print_s(s);
// 	return (free(repo), free(line), __SUCCESS);
// }

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
		// printf("%llu", new_line_size(mini));
		printf("new line = %s\n", mini->whole_cmd);
		printf("\n	==> %zu\n", __strlen(mini->whole_cmd));
	}
	return (EXIT_SUCCESS);
}
