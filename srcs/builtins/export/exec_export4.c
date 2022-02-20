/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathias <mathias@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:44:12 by malouvar          #+#    #+#             */
/*   Updated: 2022/02/20 01:08:56 by mathias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_elem(char **env, int size)
{
	__putstr("declare -x ", 1);
	__putstr(env[size], 1);
	if (in_env_from_key(env[size]))
	{
		__putstr("=", 1);
		__putchar('"', 1);
		__putstr(value_from_key(env[size]), 1);
		__putchar('"', 1);
	}
	__putstr("\n", 1);
}

void	print_sorted_env(void)
{
	char	**env;
	t_env	*lst;
	int		size;

	lst = *(s()->env_lst);
	size = env_size(lst);
	env = __malloc(sizeof(char *) * (size + 1), TRASH_STOCKAGE);
	size = 0;
	while (lst)
	{
		env[size] = __mstrdup(lst->key, TRASH_STOCKAGE);
		size++;
		lst = lst->next;
	}
	env[size] = NULL;
	sort_env(env, size);
	size = 0;
	while (env[size])
	{
		print_elem(env, size);
		size++;
	}
	__clean(TRASH_STOCKAGE);
}

t_boolean
	__incorrect_arg__(char *str)
{
	int64_t	idx;

	if (0 == __strncmp(str, "-", 1))
		return (__env_option_error__(str), __TRUE);
	idx = 0;
	while(str[idx] && ('=' != str[idx] && '+' != str[idx]))
	{
		if (__FALSE == __isalpha((int)str[idx]) && str[idx] != '_')
			return (__env_error_value__(str), __TRUE);
		idx++;
	}
	if (0 == idx)
		return (__env_error_value__(str), __TRUE);
	if ('+' == str[idx] && '=' != str[idx + 1])
		return (__env_error_value__(str), __TRUE);
	return (__FALSE);
}

t_boolean
	__is_in_lst_env__(char *key)
{
	t_env	*current;

	current = *(s()->env_lst);
	if (NULL == key)
		return (__FALSE);
	while (current)
	{
		if (!__strcmp(current->key, key))
			return (__TRUE);
		current = current->next;
	}
	return (__FALSE);
}

int	new_env_type(char *new)
{
	char	*key;
	int		idx;

	if (__TRUE == __incorrect_arg__(new))
		return (0);
	idx = 0;
	while(new[idx] && ('=' != new[idx] && '+' != new[idx]))
		idx++;
	key = __mstrldup(new, idx, ENV_STOCKAGE);
	if (new[idx] == '+' && __is_in_lst_env__(key))
		return (3);
	else if (__is_in_lst_env__(key))
		return (1);
	else
		return (2);
}
