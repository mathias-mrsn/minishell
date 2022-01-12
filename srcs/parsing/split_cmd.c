#include "minishell.h"

uint8_t
	__is_empty__(char *str)
{
	if (!str)
		return (__SUCCESS);
	while (*str)
	{
		if ((*str >= 9 && *str <= 13) || *str == ' ')
			str++;
		else
			return (__FAILURE);
	}
	return (__SUCCESS);
}

static uint64_t
	__nbr_cmd__(char *str)
{
	uint64_t	res;
	uint64_t	index;

	res = 1;
	index = 0;
	while (str[index])
	{
		if (str[index] == ';')
			res += 1;
		index += 1;
	}
	return (res);
}

static int64_t
	split_cmd(t_mini *s)
{
	char **strs;
	uint64_t	index;
	uint64_t	elem;

	index = 0;
	elem = 0;
	strs = mini_split(s->whole_cmd, ';');
	if (NULL == strs)
		return (__ERROR);
	while (strs[index])
	{
		if (__FAILURE == __is_empty__(strs[index]))
			s->cmd[elem++].full_cmd = __strtrim(strs[index], " ");
		index += 1;
	}
	return (elem);
}

uint8_t
	split_shell(t_mini *s)
{
	int64_t	split_len;

	// fonction check extra token
	if (__SUCCESS == __is_empty__(s->whole_cmd))
		return (__FAILURE);
	s->nbr_cmd = __nbr_cmd__(s->whole_cmd);
	s->cmd = (t_cmd *)__malloc(sizeof(t_cmd) * s->nbr_cmd + 1);
	if (!s->cmd)
		return (__FAILURE);
	split_len = split_cmd(s);
	if (__ERROR == split_len)
		return (__FAILURE);
	s->nbr_cmd = split_len;
	printf("[%10llu]\n", s->nbr_cmd);
	if (__FAILURE == split_pips(s))
		return (__FAILURE);
	if (__FAILURE == delete_quotes(s))
		return (__FAILURE);
	return (__SUCCESS);
}