/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:26:25 by malouvar          #+#    #+#             */
/*   Updated: 2022/02/22 17:43:16 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char
	*__get_value__(char *str)
{
	size_t	idx;

	idx = 0;
	while (str[idx] && '=' != str[idx] && '+' != str[idx])
		idx++;
	return (__mstrdup(str + idx + __trn32(str[idx] == '+', 2, 1),
			ENV_STOCKAGE));
}

char
	*__get_key__(char *str)
{
	size_t	idx;

	idx = 0;
	while (str[idx] && '=' != str[idx] && '+' != str[idx])
		idx++;
	return (__mstrldup(str, idx, ENV_STOCKAGE));
}

void	new_env(char *str)
{
	add_new_env(s()->env_lst, __mstrdup(str, ENV_STOCKAGE),
		__get_key__(str), __get_value__(str));
}

void	replace_env(char *new)
{
	t_env		*current;
	const char	*key = __get_key__(new);
	const char	*value = __get_value__(new);

	current = *(s()->env_lst);
	while (current)
	{
		if (!__strcmp(current->key, key))
		{
			current->key = (char *)key;
			current->value = (char *)value;
			current->full = new;
			current->in_env = __trn32((__strchr(new, '=') == NULL), 0, 1);
			return ;
		}
		current = current->next;
	}
}
