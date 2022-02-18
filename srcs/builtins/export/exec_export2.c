/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathias <mathias@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 15:40:15 by malouvar          #+#    #+#             */
/*   Updated: 2022/02/18 18:29:04 by mathias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_env(char **tab, int env_len)
{
	int64_t		i;
	char	*tmp;

	while (tab && tab[i] && i < env_len - 1)
	{
		if (__strncmp(tab[i], tab[i + 1], __strlen(tab[i]) + 1) > 0)
		{
			tmp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = tmp;
			i = -1;
		}
		i++;
	}
}

char	*value_from_key(char *key)
{
	t_env	*current;

	current = *(s()->env_lst);
	while (current)
	{
		if (!__strcmp(current->key, key))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

int	in_env_from_key(char *key)
{
	t_env	*current;

	current = *(s()->env_lst);
	while (current)
	{
		if (!__strcmp(current->key, key))
			return (current->in_env);
		current = current->next;
	}
	return (0);
}

int	env_size(t_env *lst)
{
	int	size;

	size = 0;
	while (lst)
	{
		size++;
		lst = lst->next;
	}
	return (size);
}


