#include "minishell.h"

char
	*__get_env_value__(t_mini *s, char *tofind)
{
	uint64_t	index;

	index = 0;
	if (!tofind)
		return (NULL);
	if (__SUCCESS == __strncmp(tofind, "?", SIZE_T_MAX))
		return (__itoa(s->exit_status));
	while (NULL != s->env[index])
	{
		if (__SUCCESS == __str_start_with(s->env[index], tofind) && s->env[index][__strlen(tofind)] == '=')
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
	s->env = malloc((size + 1) * sizeof(char *));
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
	while (str[index] && __FALSE == __is_charset(str[index], EOEV))
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
		return (NULL);
	index = 0;
	while (++index && str[index] && __FALSE == __is_charset(str[index], EOEV))
		res[index -  1] = str[index];
	res[index - 1] = '\0';
	return (res);
}