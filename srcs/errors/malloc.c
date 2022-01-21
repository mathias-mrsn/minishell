/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:54:18 by mamaurai          #+#    #+#             */
/*   Updated: 2022/01/21 10:14:01 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	__malloc_error__(char *type)
{
	__strerr(type);
	__putstr(" can't be allocate\n", 2);
	__clean();
	free(s());
	exit(__FAILURE);
}