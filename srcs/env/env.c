#include "minishell.h"


// char
// 	*__get_env_value__(t_mini *s, char *tofind)
// {
// 	uint64_t	index;

// 	index = 0;
// 	if (!tofind)
// 		return (NULL);
// 	if (__SUCCESS == __strncmp(tofind, "?", -1))
// 		return (__itoa(s->exit_status));
// 	while (NULL != s->env[index])
// 	{
// 		if (__SUCCESS == __str_start_with(s->env[index], tofind) && s->env[index][__strlen(tofind)] == '=')
// 			return (__strnstr(s->env[index], "=", -1) + 1);
// 		index++;
// 	}
// 	return (NULL);
// }

t_boolean
	str_to_lst(t_mini *s, char *str)
{
	size_t	idx;
	char	*key;
	char	*value;

	idx = 0;
	while(str[idx] && str[idx] != '=')
		idx++;
	if (0 == str[idx])
		return (__FAILURE);
	key = __mstrldup(str, idx, ENV_STOCKAGE);
	value = __mstrdup(str + idx + 1, ENV_STOCKAGE);
	add_env_back(s->env_lst, __mstrdup(str, ENV_STOCKAGE), key, value);
	return (__SUCCESS);
}

void
	__set_shell_level__(t_mini *s)
{
	t_env	*tmp;
	char	*shlvl;

	tmp = NULL;
	tmp = (*(s->env_lst));
	while (tmp)
	{
		if (0 == __strcmp(tmp->key, "SHLVL"))
		{
			shlvl = tmp->value;
			tmp->value = __mitoa(__atoi(shlvl) + 1, ENV_STOCKAGE);
		}
		tmp = tmp->next;
	}
}

uint8_t
	get_env(t_mini *s, char **env)
{
	size_t	idx;

	if (!env || !(*env))
		return (__SUCCESS);
	idx = 0;
	s->env_lst = __malloc(sizeof(t_env *), __DONT_STOCK_MEM);
	if (NULL == s->env_lst)
		return (__malloc_error__("t_env *"), __FAILURE);
	while (NULL != env[idx])
	{
		str_to_lst(s, env[idx]);
		idx++;
	}
	__set_shell_level__(s);
	return (__SUCCESS);
}

char
	**__env_to_strs__(t_mini *s)
{
	char	**strs;
	char	*begin;
	t_env	*tmp;

	tmp = NULL;
	tmp = (*(s->env_lst));
	strs = __malloc(sizeof(char *), __DONT_STOCK_MEM);
	if (NULL == strs)
		__malloc_error__("char *");
	while (tmp)
	{
		begin = __mstrjoin(tmp->key, "=", __DONT_STOCK_MEM);
		__strs_add_back(&strs,
			__mstrjoin(begin, tmp->value, __DONT_STOCK_MEM));
		tmp = tmp->next;
	}
	return (strs);
}