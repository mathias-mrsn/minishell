/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 15:08:54 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/12 11:31:38 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char
	*__get_cross__(t_mini *s)
{
	if (s->g_exit_code)
		return (__HRED"➜ "__BHCYAN" our minishell "__HYELLOW"✗ "__WHITE);
	else
		return (__HGREEN"➜ "__BHCYAN" our minishell "__HYELLOW"✗ "__WHITE);
}

void
	print_prompt(t_mini *s)
{
	s->prompt = readline(__get_cross__(s));
	add_history(s->prompt);
}
