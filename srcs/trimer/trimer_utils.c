/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trimer_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 17:31:36 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/12 11:31:21 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static uint64_t
	__get_name_len__(char *str)
{
	uint64_t	index;

	index = 0;
	while (str[index] != '=')
		index += 1;
	return (index + 1);
}

char
	*__get_env_var__(t_mini *s, char *name)
{
	uint64_t	idx;
	uint64_t	size;

	idx = 0;
	if (NULL == s->env)
		return (NULL);
	while (s->env[idx])
	{
		if (0 == __strncmp(s->env[idx], name, __strlen(name))
			&& 61 == __strcmp(s->env[idx], name))
		{
			size = __get_name_len__(s->env[idx]);
			return (__strdup(s->env[idx] + size));
		}
		idx++;
	}
	return (NULL);
}

char
	*__get_exit_code__(t_mini *s)
{
	(void)s;
	return (__itoa(s->g_exit_code));
}
