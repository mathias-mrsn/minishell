#include "minishell.h"

static uint8_t
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
			return (__FAILURE);
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
	return (free(str), __SUCCESS);
}

static int64_t
	__value_lenght__(t_mini *s, uint64_t i)
{
	char *name;
	char *value;
	int64_t	size;

	if (__SUCCESS == __is_charset(s->prompt[i + 1], " \'\"$") || !s->prompt[i + 1])
		return (1);
	name = __catch_variable_name__(s->prompt + i);
	if (!name)
		return (__ERROR);
	value = (char *)__get_env_value__(s, name);
	size = __strlen(value);
	return (size);
}

static uint64_t
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
			size += __value_lenght__(s, index);
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

static uint8_t
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
	if (__FAILURE == delete_quotes(s))
		return (__FAILURE);
	return (__clean(), __SUCCESS);
	
}

