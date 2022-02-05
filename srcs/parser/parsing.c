/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:43:00 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/05 14:35:27 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void
	cmd_parsing(t_command *cmd, t_lexer **lexer)
{
	if (cmd->command == NULL)
	{
		cmd->command = __strdup((*lexer)->argument);
		__strs_add_back(&cmd->args, __strdup((*lexer)->argument));
	}
	else
		__strs_add_back(&cmd->args, __strdup((*lexer)->argument));
	(*lexer) = (*lexer)->next;
}

t_boolean
	set_simple_right(t_mini *s, t_command *cmd, t_lexer **lexer)
{
	int 		fd;

	fd = open((*lexer)->next->argument, O_CREAT | O_TRUNC | O_RDONLY, 0644);
	if (-1 == fd)
	{
		strerror(errno);
		s->error = __TRUE;
		return (__FAILURE);
	}
	if (cmd->outfile != 0)
		close(cmd->outfile);
	cmd->outfile = fd;
	return (__SUCCESS);
}

t_boolean
	set_double_right(t_mini *s, t_command *cmd, t_lexer **lexer)
{
	int 		fd;

	fd = open((*lexer)->next->argument, O_CREAT | O_APPEND | O_RDONLY, 0644);
	if (-1 == fd)
	{
		strerror(errno);
		s->error = __TRUE;
		return (__FAILURE);
	}
	if (cmd->outfile != 0)
		close(cmd->outfile);
	cmd->outfile = fd;
	return (__SUCCESS);
}

t_boolean
	set_simple_left(t_mini *s, t_command *cmd, t_lexer **lexer)
{
	int	fd;
	
	if (__FALSE == __file_exist((*lexer)->next->argument))
		return (__file_dont_exist__(s, (*lexer)->next->argument), __FAILURE);
	fd = open((*lexer)->next->argument, O_RDONLY | O_WRONLY);
	if (-1 == fd)
		return (__FAILURE);
	if (cmd->infile != 0)
		close(cmd->infile);
	cmd->infile = fd;
	return (__SUCCESS);
}



// void
// 	manage_right_redir(t_command *cmd, t_lexer **lexer)
// {
// 	t_lexer *tmp;

// 	tmp = (*lexer);
// 	if (tmp->token == R_RIGHT)
// 	{
// 		set_simple_right(cmd, lexer);	
// 	}
// 	// else if (tmp->token == DR_RIGHT)
// 	// {
// 	// 	if (tmp->prev == NULL)
// 	// 		heredoc_set();
// 	// 	else
// 	// 		set_double_right();
// 	// }	
// }

// void
// 	redir_parsing(t_command *cmd, t_lexer **lexer)
// {
// 	t_lexer *tmp;

// 	tmp = (*lexer);
// 	if (tmp->token == R_RIGHT || tmp->token == DR_RIGHT)
// 		manage_right_redir(cmd, lexer);
// 	// else if (tmp->token == R_LEFT || tmp->token == DR_LEFT)
// 	// 	manage_left_redir();
// 	(*lexer) = (*lexer)->next->next;
// }

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

void
	output_parsing(t_mini *s, t_command *cmd, t_lexer **lexer)
{
	if ((*lexer)->token == R_RIGHT)
		set_simple_right(s, cmd, lexer);
	if ((*lexer)->token == DR_RIGHT)
		set_double_right(s, cmd, lexer);
	(*lexer) = (*lexer)->next->next;
}

void
	input_parsing(t_mini *s, t_command *cmd, t_lexer **lexer)
{
	if ((*lexer)->token == R_LEFT)
		set_simple_left(s, cmd, lexer);
	else if ((*lexer)->token == DR_LEFT)
		set_here_doc(s, cmd, lexer);
	(*lexer) = (*lexer)->next->next;
}

void
	cmd_parsing_hub(t_mini *s)
{
	t_lexer 	*tmp;
	t_command	*cmd;

	tmp = s->lexer;
	cmd = add_command_front(&s->cmd);

	while (tmp)
	{
		if (tmp->token == ARGS)
			cmd_parsing(cmd, &tmp);
		else if (tmp->token == R_LEFT || tmp->token == DR_LEFT)
			input_parsing(s, cmd, &tmp);
		else if (tmp->token == R_RIGHT || tmp->token == DR_RIGHT)
			output_parsing(s, cmd, &tmp);
		else if (tmp->token == PIP)
		{
			cmd = add_command_back(&s->cmd);
			tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
}

t_boolean
	show_cmd(void)
{
	t_command *cmd;
	int i;

	cmd = s()->cmd;

	while(cmd)
	{
		i = 0;
		if (cmd->command)
			printf("cmd = %s\n", cmd->command);
		if (cmd->args)
		{
			while(cmd->args[i])
			{
				printf("%s - ", cmd->args[i]);
				i++;
			}
		}
		printf("infile = %d\n", cmd->infile);
		printf("outfile = %d\n", cmd->outfile);
		cmd = cmd->next;
		printf("\n\n");
	}
	return (__SUCCESS);
}

void
	show_token(void)
{
	t_lexer *tmp = s()->lexer;

	printf("TOKEN :\n\n");
	while(tmp)
	{
		printf(" -> ");
		if (tmp->token == ARGS)
			printf("ARGS");
		else if (tmp->token == DR_LEFT)
			printf("DR_LEFT");
		else if (tmp->token == DR_RIGHT)
			printf("DR_RIGHT");
		else if (tmp->token == R_LEFT)
			printf("R_LEFT");
		else if (tmp->token == R_RIGHT)
			printf("R_LEFT");
		else if (tmp->token == PIP)
			printf("PIP");
		tmp = tmp->next;
	}
	printf("\n\n");
}

t_boolean
	parsing(t_mini *s)
{
	if (NULL == s->lexer)
		return (__SUCCESS);
	show_token();
	cmd_parsing_hub(s);
	show_cmd();
	return (__SUCCESS);
}

// DR_LEFT - ARGS - ARGS - PIP - ARGS

// heredoc
// execute cmd
// |
// |
// execute cmd
