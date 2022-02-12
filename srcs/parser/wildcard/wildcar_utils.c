/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcar_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 16:28:48 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/12 11:39:48 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_boolean
	__file_match_with_wc__(char *file, const char **wc, int start, int end)
{
	const size_t	wc_len = (const size_t)__strslen((char **)wc) - 1;
	size_t			idx;
	size_t			wc_idx;

	wc_idx = 0;
	idx = 0;
	while (file[idx] && wc_idx <= wc_len)
	{
		if (start == 0 && wc_idx == 0
			&& __strncmp(file, wc[0], __strlen(wc[0])) != 0)
			return (__FAILURE);
		if (end == 0 && wc_idx == wc_len
			&& __strncmp(file + __strlen(file) - __strlen(wc[wc_len]),
				wc[wc_len], __strlen(wc[wc_len])))
			return (__FAILURE);
		if (wc[wc_idx] && __strncmp(file + idx, wc[wc_idx],
				__strlen(wc[wc_idx])) == 0)
			idx += __strlen(wc[wc_idx++]);
		else
			idx++;
	}
	if (wc_idx == wc_len + 1)
		return (__SUCCESS);
	return (__FAILURE);
}

void
	__swap__(char **a, char **b)
{
	char	*tmp;

	tmp = (*a);
	(*a) = (*b);
	(*b) = tmp;
}

void
	__sort_args__(char ***list)
{
	size_t	idx;

	idx = 0;
	while ((*list)[idx] && (*list)[idx + 1])
	{
		if (__strcmp((*list)[idx], (*list)[idx + 1]) > 0)
		{
			__swap__(&(*list)[idx], &(*list)[idx + 1]);
			idx = 0;
		}
		else
			idx++;
	}
}

void
	__add_to_cmd__(t_command *cmd, char **strs, char *add_front)
{
	size_t	idx;

	idx = 0;
	while (strs[idx])
	{
		__strs_add_back(&cmd->args, __strjoin(add_front, strs[idx]));
		idx++;
	}
}
