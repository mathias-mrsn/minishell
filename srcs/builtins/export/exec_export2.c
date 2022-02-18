/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malouvar <malouvar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 15:40:15 by malouvar          #+#    #+#             */
/*   Updated: 2022/02/15 16:44:31 by malouvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_env(char **tab, int env_len)
{
	int		ordered;
	int		i;
	char	*tmp;

	ordered = 0;
	while (tab && ordered == 0)
	{
		ordered = 1;
		i = 0;
		while (i < env_len - 1)
		{
			if (__strncmp(tab[i], tab[i + 1], __strlen(tab[i]) + 1) > 0)
			{
				tmp = tab[i];
				tab[i] = tab[i + 1];
				tab[i + 1] = tmp;
				ordered = 0;
			}
			i++;
		}
		env_len--;
	}
}

char	*value_from_key(char *key)
{
	t_env	*current;

	current = *(s()->env_lst);
	while (current)
	{
		if (!__strncmp(current->key, key, (__strlen(key) + 1)))
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
		if (!__strncmp(current->key, key, (__strlen(key) + 1)))
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
