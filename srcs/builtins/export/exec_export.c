/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_export.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathias <mathias@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:28:50 by malouvar          #+#    #+#             */
/*   Updated: 2022/02/18 18:23:52 by mathias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	concat_env(char *new)
{
	t_env		*current;
	const char	*key = __get_key__(new);
	const char	*value = __get_value__(new);
	char		*tmp;

	current = *(s()->env_lst);
	while(current)
	{
		if (!__strcmp(current->key, key))
		{
			tmp = current->value;
			current->value = __mstrjoin(tmp, value, ENV_STOCKAGE);
			tmp = current->full;
			current->full = __mstrjoin(tmp, value, ENV_STOCKAGE);
			current->in_env = 1;
			return ;
		}
		current = current->next;
	}
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
			if (type == 1)
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
