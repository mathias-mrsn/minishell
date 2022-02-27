/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_d.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 17:10:25 by malouvar          #+#    #+#             */
/*   Updated: 2022/02/22 18:11:05 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_D_H
# define MINISHELL_D_H

# define TOO_MANY_ARG_ERR "minishell: too many arguments to launch\n"

# define PROGRAM_NAME "minishell"
# define OPTION_CHARSET "-"
# define TOKEN_CS "|>< "
# define NBR_BUILDINS 7

/*
**	DICT	
*/

# define DICT_SIZE 23
# define DICT_LEFT 0
# define DICT_MIDDLE 1
# define DICT_RIGHT 2

/*
**	MALLOC
*/

# define LEXER_STOCKAGE	3
# define COMMAND_STOCKAGE 4
# define ENV_STOCKAGE 2
# define TRASH_STOCKAGE 127
# define GLOB_S_STOCKAGE 42

/*
**	PROG_STATES
*/

# define HEREDOC_CHILD 1
# define HEREDOC_FATHER 2
# define OUT_OF_SHELL 3
# define SHELL	42

#endif