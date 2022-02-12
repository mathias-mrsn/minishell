/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singleton.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/12 11:45:55 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/12 11:46:07 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_mini
	*s(void)
{
	static t_mini	*s;

	if (!s)
	{
		s = malloc(sizeof(t_mini) * 1);
		__memset(s, 0, sizeof(t_mini));
		if (!s)
			return (NULL);
	}
	return (s);
}
