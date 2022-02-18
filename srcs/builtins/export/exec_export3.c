/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malouvar <malouvar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:26:25 by malouvar          #+#    #+#             */
/*   Updated: 2022/02/16 11:38:43 by malouvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_env(char *str)
{
	size_t	idx;
	char	*key;
	char	*value;

	idx = 0;
	while (str[idx] && str[idx] != '=')
		idx++;
	key = __mstrldup(str, idx, ENV_STOCKAGE);
	value = __mstrdup(str + idx + 1, ENV_STOCKAGE);
	add_new_env(s()->env_lst, __mstrdup(str, ENV_STOCKAGE), key, value);
}

void	replace_env(char *new)
{
	char	**splited;
	t_env	*current;

	splited = __msplit(new, '=', __DONT_STOCK_MEM);
	current = *(s()->env_lst);
	while (current)
	{
		if (!__strncmp(current->key, splited[0], (__strlen(splited[0]) + 1)))
		{
			free(current->value);
			if (splited[1])
				current->value = splited[1];
			else
				current->value = NULL;
			if (__strchr(new, '='))
				current->in_env = 1;
			free(splited[0]);
			free(splited);
			current->full = new;
			return ;
		}
		current = current->next;
	}
}

void	invalid_env(char *new)
{
	write(2, "export: ", 8);
	write(2, new, __strlen(new));
	write(2, ": not a valid identifier\n", 25);
	s()->g_exit_code = 1;
}
