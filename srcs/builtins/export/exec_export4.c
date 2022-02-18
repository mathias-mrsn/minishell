/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malouvar <malouvar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:44:12 by malouvar          #+#    #+#             */
/*   Updated: 2022/02/16 11:35:55 by malouvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_sorted_env(void)
{
	char	**env;
	t_env	*lst;
	int		size;

	lst = *(s()->env_lst);
	size = env_size(lst);
	env = malloc(sizeof(char *) * (size + 1));
	size = 0;
	lst = *(s()->env_lst);
	while (lst)
	{
		env[size] = __mstrdup(lst->key, __DONT_STOCK_MEM);
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
}

void	free_splited_export(char **splited)
{
	free(splited[0]);
	if (splited[1])
		free(splited[1]);
	free(splited);
}

int	new_env_type(char *new)
{
	char	**splited;
	t_env	*current;
	int		concat;

	concat = 0;
	if (!__isalpha(new[0]))
		return (0);
	splited = __msplit(new, '=', __DONT_STOCK_MEM);
	current = *(s()->env_lst);
	if (splited[0][__strlen(splited[0]) - 1] == '+')
		concat = 1;
	while (current)
	{
		if (!__strncmp(splited[0], current->key, (__strlen(splited[0])
					- concat)) && !current->key[__strlen(splited[0])])
		{
			if (concat)
				return (free_splited_export(splited), 3);
			return (free_splited_export(splited), 1);
		}
		else
			current = current->next;
	}
	return (free_splited_export(splited), 2);
}
