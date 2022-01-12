#include "minishell.h"

static uint64_t
	__nbr_pip__(char *str)
{
	uint64_t	res;
	uint64_t	index;

	res = 1;
	index = 0;
	while (str[index])
	{
		if (str[index] == '|')
			res += 1;
		index += 1;
	}
	return (res);
}

static t_pip
	*cmd_to_pip(t_cmd *cmd)
{
	t_pip		*res;
	char		**strs;
	uint64_t	index;
	uint64_t	elem;
	
	elem = 0;
	index = 0;
	res = (t_pip *)__malloc(sizeof(t_pip) * cmd->nbr_pip + 1);
	if (!res)
		return (NULL);
	strs = mini_split(cmd->full_cmd, '|');
	if (NULL == strs)
		return (NULL);
	while (index < cmd->nbr_pip)
	{
		if (__FAILURE == __is_empty__(strs[index]))
			res[elem++].full = __strtrim(strs[index], " ");
		index += 1;
	}
	cmd->nbr_pip = elem;
	return (res);
}

uint8_t
	split_pips(t_mini *s)
{
	uint64_t	i;

	i = 0;
	while (i < s->nbr_cmd)
	{

		s->cmd[i].nbr_pip = __nbr_pip__(s->cmd[i].full_cmd);
		s->cmd[i].pip = cmd_to_pip(&s->cmd[i]);
		if (NULL == s->cmd[i].pip)
			return (__FAILURE);
		i++;
	}
	return (__SUCCESS);
}