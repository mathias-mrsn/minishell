/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malouvar <malouvar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:26:45 by malouvar          #+#    #+#             */
/*   Updated: 2022/02/16 11:28:08 by malouvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_env(void)
{
	t_env	*env;

	env = *(s()->env_lst);
	if (!env)
		exit (1);
	while (env)
	{
		if (env->in_env == 1)
		{
			__putstr(env->key, 1);
			__putstr("=", 1);
			__putstr(env->value, 1);
			__putchar('\n', 1);
		}
		env = env->next;
	}
}
