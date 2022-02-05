/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:53:30 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/05 13:22:21 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	__token_syntax_error__(t_mini *s, int error_value)
{
	const char *error[6] = {"|", "<", ">", "<<", ">>", "newline"};

	__putstr(PROGRAM_NAME, 2);
	__putstr(": syntax error near unexpected token `", 2);
	__putstr((char *)error[error_value], 2);
	__putstr("'\n", 2);
	s->error = __TRUE;
}

void
	__unclosed_quote__(t_mini *s, int error_value)
{
	const char *error[2] = {"\'", "\""};
	
	__putstr(PROGRAM_NAME, 2);
	__putstr(": unclosed token detected `", 2);
	__putstr((char *)error[error_value], 2);
	__putstr("'\n", 2);
	s->error = __TRUE;
}

void
	__file_dont_exist__(t_mini *s, char *str)
{
	__putstr(PROGRAM_NAME, 2);
	__putstr(": ", 2);
	__putstr(str, 2);
	__putstr(": No such file or directory", 2);
	__putstr("'\n", 2);
	s->error = __TRUE;
}