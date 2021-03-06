/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pwd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 15:45:37 by malouvar          #+#    #+#             */
/*   Updated: 2022/02/22 17:44:00 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_pwd(t_command *cmd)
{
	char	*buf;

	(void)cmd;
	buf = NULL;
	buf = getcwd(buf, 999999);
	if (!buf)
		exit (1);
	__putstr(buf, 1);
	__putchar('\n', 1);
	free(buf);
}
