/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:20:15 by mamaurai          #+#    #+#             */
/*   Updated: 2022/01/30 18:34:05 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	__token_syntax_error__(int error_value)
{
	const char *error[5] = {"|", "<", ">", "<<", ">>"};

	__putstr((char *)error[error_value], 2);
}

void
	*__create_dictionary__(void)
{
	static const t_dict dict[2] = {{{ARGS, ARGS, R_RIGHT}, 1}, {{ARGS, ARGS, R_RIGHT}, 2}};

	printf("%p\n", dict);
	printf("%p\n", &dict[0]);
	printf("%p\n", &dict[1]);
	return ((void *)dict);
}

t_boolean
	lexer_checker(t_mini *s)
{
	const t_dict *dict = (const t_dict *)__create_dictionary__();
	// int i = 0;
	printf("\n\n");
	printf("%p\n", dict);
	printf("%p\n", &dict[0]);
	printf("%p\n", &dict[1]);
	// while(i < 1)
	// {
		// if (dict[0][0] == ARGS)
		// 	printf("here");
	// 	i++;
	// } 
	(void)dict;
	(void)s;
	return (__SUCCESS);
}