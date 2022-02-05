/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 17:53:58 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/05 17:54:18 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(t_mini *s, t_command *cmd)
{
	int		fd;
	char	*line;

	(void)s;
	(void)line;
	fd = open(".heredoc_tmp", O_CREAT | O_WRONLY | O_TRUNC, 0000644);
	if (fd < 0)
		perror("Error while creating Heredoc!");
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = readline("");
		if (!line || !__strncmp(cmd->limiter, line, __strlen(cmd->limiter)))
			break ;
		write(fd, line, __strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	free(line);
	close(fd);
	cmd->infile = open(".heredoc_tmp", O_RDONLY);
	if (cmd->infile < 0)
	{
		unlink(".heredoc_tmp");
		perror("Infile error !");
	}
}

//TRIM DOLLAR IN HEREDOC

t_boolean
	set_here_doc(t_mini *s, t_command *cmd, t_lexer **lexer)
{
	(void)s;
	cmd->limiter = __strdup((*lexer)->next->argument);
	if (cmd->limiter == NULL)
		return (__FAILURE);
	heredoc(s, cmd);
	return (__SUCCESS);
}