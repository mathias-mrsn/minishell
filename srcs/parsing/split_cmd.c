#include "minishell.h"

uint64_t
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

uint64_t
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

uint8_t
	split_cmd(t_mini *s)
{
	char **strs;
	uint64_t	index;

	index = 0;
	strs = __split(s->whole_cmd, ';');
	if (NULL == strs)
		return (__FAILURE);
	while (strs[index])
	{
		s->cmd[index].full_cmd = __strtrim(strs[index], " ");
		// free(strs[index]);
		index += 1;
	}
	return (__SUCCESS);
}


t_pip
	*cmd_to_pip(t_cmd cmd)
{
	t_pip	*res;
	char	**strs;
	uint64_t	index;
	
	index = 0;
	res = (t_pip *)__malloc(sizeof(t_pip) * cmd.nbr_pip + 1);
	if (!res)
		return (NULL);
	strs = __split(cmd.full_cmd, '|');
	if (NULL == strs)
		return (NULL);
	while (index < cmd.nbr_pip)
	{
		res[index].command = __strtrim(strs[index], " ");
		// free(strs[index]);
		index += 1;
	}
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
		s->cmd[i].pip = cmd_to_pip(s->cmd[i]);
		if (NULL == s->cmd[i].pip)
			return (__FAILURE);
		i++;
	}
	return (__SUCCESS);
}

uint8_t
	__check_empty_pip__(char *str)
{
	if (!str)
		return (__FAILURE);
	while (*str)
	{
		if ((*str >= 9 && *str <= 13) || *str == ' ')
			str++;
		else
			return (__SUCCESS);
	}
	return (__FAILURE);
}

uint8_t
	__check_commands__(t_mini *s)
{
	uint64_t	index_cmd;
	uint64_t	index_pip;

	index_cmd = 0;
	while (index_cmd < s->nbr_cmd)
	{
		index_pip = 0;
		while (index_pip < s->cmd[index_cmd].nbr_pip)
		{
			if (__FAILURE == __check_empty_pip__(s->cmd[index_cmd].pip[index_pip].command))
				return (__putstr(PIP_ERR, 2), __FAILURE);
			index_pip += 1;
		}
		index_cmd += 1;
	}
	return (__SUCCESS);
}



uint8_t
	split_shell(t_mini *s)
{
	// fonction check extra token
	if (__FAILURE == __check_empty_pip__(s->whole_cmd))
		return (__FAILURE);
	s->nbr_cmd = __nbr_cmd__(s->whole_cmd);
	printf("[%10llu]\n", s->nbr_cmd);
	// s->cmd = (t_cmd *)__malloc(sizeof(t_cmd) * s->nbr_cmd + 1);
	// if (!s->cmd)
	// 	return (__FAILURE);
	// if (__FAILURE == split_cmd(s))
	// 	return (__FAILURE);
	// if (__FAILURE == split_pips(s))
	// 	return (__FAILURE);
	// if (__FAILURE == __check_commands__(s))
	// 	return (__FAILURE);	
	return (__SUCCESS);
}