/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 09:54:18 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/12 11:57:22 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	__malloc_error__(char *type)
{
	__puterr(type);
	__putstr(" can't be allocate\n", 2);
	__clean_all();
	free(s());
	exit(__FAILURE);
}
