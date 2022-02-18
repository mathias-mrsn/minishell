/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_unset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 15:47:50 by malouvar          #+#    #+#             */
/*   Updated: 2022/02/17 10:47:33 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unvalid(char *arg)
{
	write(2, "unset: ", 7);
	write(2, arg, __strlen(arg));
	write(2, ": not a valid identifier\n", 25);
	s()->g_exit_code = 127;
}

void	unset_elem(t_env *env, t_env *previous)
{
	if (previous)
		previous->next = env->next;
	else
		s()->env_lst = &(env->next);
}

void	start_unset(t_command *cmd, t_env *env, t_env *previous, int ret)
{
	int	i;

	i = 0;
	while (cmd->args[++i])
	{
		ret = 1;
		env = *(s()->env_lst);
		previous = NULL;
		while (env)
		{
			if (!__strncmp(cmd->args[i], env->key,
					(__strlen(cmd->args[i]) + 1)))
			{
				unset_elem(env, previous);
				ret = 0;
				break ;
			}
			previous = env;
			env = env->next;
		}
		if (ret)
			unvalid(cmd->args[i]);
	}
}

void	exec_unset(t_command *cmd)
{
	t_env	*env;
	t_env	*previous;
	int		ret;

	env = NULL;
	previous = NULL;
	ret = 1;
	start_unset(cmd, env, previous, ret);
}
