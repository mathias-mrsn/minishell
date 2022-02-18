/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 11:45:55 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/16 11:50:08 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mini
	*s(void)
{
	static t_mini	*s;

	if (!s)
	{
		s = __malloc(sizeof(t_mini), GLOB_S_STOCKAGE);
		if (!s)
			return (NULL);
	}
	return (s);
}
