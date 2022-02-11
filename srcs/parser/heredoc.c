/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 17:53:58 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/11 12:16:15 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void
	__heredoc_dollars_change__(t_mini *s, char **str, uint64_t *idx)
{
	uint64_t	end;
	char		*begin;
	char		*var;
	char		*var_value;
	char		*final;

	begin = __mstrldup((*str), (*idx), TRASH_STOCKAGE);
	end = (*idx) + 1;
	if ((*str)[(*idx) + 1] == '?')
	{
		end += 1;
		var_value = __mitoa(s->g_exit_code, TRASH_STOCKAGE);
	}
	else
	{
		while(__isalnum((*str)[end]) || (*str)[end] == '_')
			end++;
		var = __mstrldup((*str) + (*idx) + 1, end - (*idx) - 1, TRASH_STOCKAGE);
		var_value = value_from_key(var);
	}
	final = __strjoin(begin, __mstrjoin(var_value, __mstrdup((*str) + end, TRASH_STOCKAGE), TRASH_STOCKAGE));
	(*idx) += __strlen(var_value);
	(*str) = final;
}

static char
	*heredoc_dollars(t_mini *s, char *str)
{
	uint64_t	idx;

	idx = 0;
	while(str[idx])
	{
		if (str[idx] == DOLLAR)
			__heredoc_dollars_change__(s, &str, &idx);
		else
			idx++;
	}
	return (str);
}

void	heredoc(t_mini *s, t_command *cmd)
{
	int		fd;
	char	*line;
	char 	*dollar_trimed;

	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd < 0)
		perror("minishell: .heredoc_tmp cannot be created");
	while (1)
	{
		line = readline("> ");
		if (!line || !__strncmp(cmd->limiter, line, __strlen(cmd->limiter)))
			break ;
		dollar_trimed = heredoc_dollars(s, line);
		write(fd, dollar_trimed, __strlen(dollar_trimed));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
	exit(0);
}

void
	fork_heredoc(t_mini *s, t_command *cmd)
{
	pid_t	pid;
	int		return_value;

	pid = fork();
	return_value = 0;
	if (pid == 0)
	{
		s->prog_state = HEREDOC_CHILD;
		heredoc(s, cmd);
	}
	else
	{
		s->prog_state = HEREDOC_FATHER;
		waitpid(pid, &return_value, 0);
	}
	s->prog_state = 0;
	cmd->infile = open(".heredoc_tmp", O_RDONLY);
	if (cmd->infile < 0)
	{
		unlink(".heredoc_tmp");
		perror("minishell: .heredoc_tmp cannot be opened");
	}
}

t_boolean
	set_here_doc(t_mini *s, t_command *cmd, t_lexer **lexer)
{
	(void)s;
	cmd->limiter = __strdup((*lexer)->next->argument);
	if (cmd->limiter == NULL)
		return (__FAILURE);
	fork_heredoc(s, cmd);
	// heredoc(s, cmd);
	return (__SUCCESS);
}
