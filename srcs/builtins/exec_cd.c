/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malouvar <malouvar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 14:08:08 by malouvar          #+#    #+#             */
/*   Updated: 2022/02/16 12:08:29 by malouvar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_pwd(char *old)
{
	char	*buf;

	buf = NULL;
	buf = getcwd(buf, 999999);
	if (value_from_key("OLDPWD"))
		replace_env(__strjoin("OLDPWD=", old));
	else
		new_env(__strjoin("OLDPWD=", old));
	if (value_from_key("PWD"))
		replace_env(__strjoin("PWD=", buf));
	free(buf);
}

void	cd_home(char *buf)
{
	char	*home;

	home = value_from_key("HOME");
	if (home)
	{
		chdir(home);
		replace_pwd(buf);
	}
	else
		__putstr("minishell: cd: HOME not set\n", 2);
	free(buf);
}

void	path_error(char *path, char *buf)
{
	__putstr("minishell: cd: ", 2);
	__putstr(path, 2);
	__putstr(": No such file or directory\n", 2);
	free(buf);
	s()->g_exit_code = 127;
}

void	exec_cd(t_command *cmd)
{
	char	*buf;

	buf = NULL;
	buf = getcwd(buf, 999999);
	if (cmd->args[2])
	{
		__putstr("minishell: cd: too many arguments\n", 2);
		free(buf);
		s()->g_exit_code = 1 ;
	}
	else if (!(cmd->args[1]))
		return (cd_home(buf));
	else if (chdir(cmd->args[1]))
		return (path_error(cmd->args[1], buf));
	else
	{
		replace_pwd(buf);
		free(buf);
	}
}
