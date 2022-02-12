/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_msg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 15:53:30 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/12 11:57:15 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	__token_syntax_error__(t_mini *s, int error_value)
{
	const char	*error[6] = {"|", "<", ">", "<<", ">>", "newline"};

	__putstr(PROGRAM_NAME, 2);
	__putstr(": syntax error near unexpected token `", 2);
	__putstr((char *)error[error_value], 2);
	__putstr("'\n", 2);
	s->error = __TRUE;
	s->g_exit_code = 258;
}

void
	__unclosed_quote__(t_mini *s, int error_value)
{
	const char	*error[2] = {"\'", "\""};

	__putstr(PROGRAM_NAME, 2);
	__putstr(": unclosed token detected `", 2);
	__putstr((char *)error[error_value], 2);
	__putstr("'\n", 2);
	s->error = __TRUE;
	s->g_exit_code = 258;
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
	s->g_exit_code = 1;
}

void
	__error_wildcard__(t_mini *s)
{
	s->g_exit_code = 1;
	s->error = __TRUE;
	__putstr(PROGRAM_NAME, STDERR_FILENO);
	__putstr(": wildcards used out of the current directory\n", STDERR_FILENO);
	s->g_exit_code = 1;
}
