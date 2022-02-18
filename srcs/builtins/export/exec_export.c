/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malouvar <malouvar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:28:50 by malouvar          #+#    #+#             */
/*   Updated: 2022/02/15 16:37:34 by malouvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_splited(char *tmp, char **splited)
{
	if (tmp)
		free(tmp);
	if (splited[0])
		free(splited[0]);
	if (splited[1])
		free(splited[1]);
}

void	loop_concat_env(char **splited, t_env *current, char *tmp)
{
	while (current)
	{
		if (!__strncmp(current->key, splited[0], (__strlen(current->key)))
			&& splited[0][__strlen(current->key)] == '+')
		{
			if (splited[1])
			{
				tmp = __mstrjoin(current->value, splited[1], __DONT_STOCK_MEM);
				free(current->value);
				current->value = tmp;
			}
			splited[0][__strlen(splited[0]) - 1] = 0;
			tmp = __mstrjoin(splited[0], "=", __DONT_STOCK_MEM);
			free(current->full);
			if (current->value)
				current->full = __mstrjoin(tmp,
						current->value, __DONT_STOCK_MEM);
			else
				current->full = __mstrdup(tmp, __DONT_STOCK_MEM);
			current->in_env = 1;
			free_splited(tmp, splited);
			return ;
		}
		current = current->next;
	}
}

void	concat_env(char *new)
{
	char	**splited;
	t_env	*current;
	char	*tmp;

	splited = __msplit(new, '=', __DONT_STOCK_MEM);
	current = *(s()->env_lst);
	tmp = NULL;
	loop_concat_env(splited, current, tmp);
}

void	exec_export(t_command *cmd)
{
	int	i;
	int	type;

	if (!cmd->args[1])
		print_sorted_env();
	else
	{
		i = 1;
		while (cmd->args[i])
		{
			type = new_env_type(cmd->args[i]);
			if (!type)
				invalid_env(cmd->args[i]);
			else if (type == 1)
				replace_env(cmd->args[i]);
			else if (type == 2)
				new_env(cmd->args[i]);
			else if (type == 3)
				concat_env(cmd->args[i]);
			i++;
		}
	}
	return ;
}
