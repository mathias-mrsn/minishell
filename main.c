/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mathias <mathias@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 23:37:55 by mathias           #+#    #+#             */
/*   Updated: 2022/02/20 00:07:28 by mathias          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int
	main(int argc, char **argv)
{
	char *a = __malloc(23453, 4);
	char *b = __strdup("str");
	char *c = __strjoin("yo", "ca va");
	char *d = malloc(432);
	__print_memory();
	if (__is_in_my_memory(c))
		__printf("here\n");
	__free(a);
	__print_memory();
	return (0);
}