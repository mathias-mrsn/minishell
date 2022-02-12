/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wilcard_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 11:43:40 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/12 12:04:00 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	__get_start__(char *str)
{
	if (!str)
		return (__ERROR);
	if (str[0] == '*')
		return (1);
	else
		return (0);
}

int
	__get_end__(char *str)
{
	if (!str)
		return (__ERROR);
	if (str[__strlen(str) - 1] == '*')
		return (1);
	else
		return (0);
}

t_boolean
	__open_dir__(DIR **dir)
{
	(*dir) = opendir(".");
	if (NULL == (*dir))
		return (strerror(errno), __FAILURE);
	else
		return (__SUCCESS);
}

void
	__get_list__(char ***list, DIR *dir)
{
	struct dirent	*dirent;

	dirent = __malloc(sizeof(struct dirent), 1);
	if (!dirent)
		__malloc_error__("dirent");
	dirent = readdir(dir);
	while (dirent)
	{
		__strs_add_back(list, dirent->d_name);
		dirent = readdir(dir);
	}
}
