/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_env_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 11:47:58 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/12 18:59:45 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env
	*create_env(char *full, char *key, char *value)
{
	t_env	*env;

	env = NULL;
	env = __malloc(sizeof(t_env), __DONT_STOCK_MEM);
	if (NULL == env)
		return (__malloc_error__("t_env"), NULL);
	__bzero(env, sizeof(t_env));
	env->full = full;
	env->key = key;
	env->value = value;
	env->in_env = __trn32((__strchr(full, '=') == NULL), 0, 1);
	return (env);
}

t_boolean
	add_env_back(t_env **head, char *full, char *key, char *value)
{
	t_env	*tmp;

	if (NULL == head)
		return (__FAILURE);
	tmp = (*head);
	if (NULL == tmp)
		(*head) = create_env(full, key, value);
	else
	{
		while (NULL != tmp)
		{
			if (NULL == tmp->next)
			{
				tmp->next = create_env(full, key, value);
				return (__SUCCESS);
			}
			tmp = tmp->next;
		}
	}
	return (__SUCCESS);
}

t_boolean
	add_new_env(t_env **head, char *full, char *key, char *value)
{	
	t_env	*tmp;
	t_env	*save;

	if (NULL == head)
		return (__FAILURE);
	tmp = (*head);
	if (NULL == tmp)
		(*head) = create_env(full, key, value);
	else
	{
		while (NULL != tmp)
		{
			if (NULL == tmp->next || 0 == __strcmp(tmp->next->key, "_"))
			{
				save = tmp->next;
				tmp->next = create_env(full, key, value);
				tmp->next->next = save;
				return (__SUCCESS);
			}
			tmp = tmp->next;
		}
	}
	return (__SUCCESS);
}

size_t
	__env_lst_length__(t_env **head)
{
	t_env	*tmp;
	size_t	length;

	tmp = NULL;
	length = 0;
	if (!head || !(*(head)))
		return (0);
	tmp = (*(head));
	while(tmp)
	{
		length += 1;
		tmp = tmp->next;
	}
	return (length);
}
