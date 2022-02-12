/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 16:26:23 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/12 11:44:08 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	create_list(char ***final_list, char **list, char *str)
{
	const char	**wc_splited = (const char **)__split(str, '*');
	uint64_t	idx;

	idx = 0;
	while (list[idx])
	{
		if (str[0] == '.' && list[idx][0] == '.'
			&& (!__file_match_with_wc__(list[idx], wc_splited,
				__get_start__(str), __get_end__(str)) || wc_splited == NULL))
			__strs_add_back(final_list, list[idx]);
		if (list[idx][0] != '.' && str[0] != '.'
			&& (!__file_match_with_wc__(list[idx], wc_splited,
				__get_start__(str), __get_end__(str)) || wc_splited == NULL))
			__strs_add_back(final_list, list[idx]);
		idx++;
	}	
}

static char
	**replace_wildcard(char *str)
{
	DIR		*dir;
	char	**list;
	char	**final_list;

	list = NULL;
	final_list = NULL;
	if (__FAILURE == __open_dir__(&dir))
		return (NULL);
	__get_list__(&list, dir);
	create_list(&final_list, list, str);
	return (final_list);
}

void
	wildcard(t_mini *s, t_command *cmd, char *str)
{
	char	**args;
	char	*add_front;

	args = NULL;
	add_front = NULL;
	if (__str_count(str, '/') == 0)
		args = replace_wildcard(str);
	else if (__strncmp(str, "./", 2) == 0 && __str_count(str, '/') == 1)
	{
		add_front = __strdup("./");
		args = replace_wildcard(str + 2);
	}
	else
		__error_wildcard__(s);
	if (NULL != args)
	{
		__sort_args__(&args);
		__add_to_cmd__(cmd, args, add_front);
	}
	else
		__strs_add_back(&cmd->args, str);
}
