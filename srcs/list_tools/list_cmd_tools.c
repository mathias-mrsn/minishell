/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_cmd_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 15:17:36 by mamaurai          #+#    #+#             */
/*   Updated: 2022/01/25 16:55:10 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command
	*create_command(t_command *next, t_command *prev)
{
	t_command *cmd;

	cmd = NULL;
	cmd = (t_command *)__malloc(sizeof(t_command), COMMAND_STOCKAGE);
	if (NULL == cmd)
		return (__malloc_error__("t_command"), NULL);
	__bzero(cmd, sizeof(t_command));
	cmd->prev = prev;
	cmd->next = next;
	return (cmd);
}

t_command
	*add_command_back(t_command **head)
{
	t_command *tmp;

	if (NULL == head)
		return (NULL);
	tmp = (*head);
	if (NULL == tmp)
		(*head) = create_command(NULL, NULL);
	else
	{
		while (NULL != tmp)
		{
			if (NULL == tmp->next)
			{
				tmp->next = create_command(NULL, tmp);
				return (tmp->next);
			} 
			tmp = tmp->next;
		}
	}
	return ((*head));
}

t_command
	*add_command_front(t_command **head)
{
	t_command *tmp;

	if (NULL == head)
		return (NULL);
	tmp = (*head);
	if (NULL == tmp)
		(*head) = create_command(NULL, NULL);
	else
		(*head) = create_command(tmp, NULL);
	return ((*head));
}