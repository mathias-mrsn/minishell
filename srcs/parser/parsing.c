/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:43:00 by mamaurai          #+#    #+#             */
/*   Updated: 2022/01/28 18:13:51 by mamaurai         ###   ########.fr       */
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

void
	set_simple_right(t_command *cmd, t_lexer **lexer)
{
	int 		fd;
	t_lexer 	*tmp;

	tmp = (*lexer);
	fd = open(tmp->next->argument, O_CREAT | O_TRUNC | O_RDONLY, 0644);
	if (-1 == fd)
		return ;
	cmd->outfile = fd;
}

void
	manage_right_redir(t_command *cmd, t_lexer **lexer)
{
	t_lexer *tmp;

	tmp = (*lexer);
	if (tmp->token == R_RIGHT)
	{
		set_simple_right(cmd, lexer);	
	}
	// else if (tmp->token == DR_RIGHT)
	// {
	// 	if (tmp->prev == NULL)
	// 		heredoc_set();
	// 	else
	// 		set_double_right();
	// }	
}

void
	redir_parsing(t_command *cmd, t_lexer **lexer)
{
	t_lexer *tmp;

	tmp = (*lexer);
	if (tmp->token == R_RIGHT || tmp->token == DR_RIGHT)
		manage_right_redir(cmd, lexer);
	// else if (tmp->token == R_LEFT || tmp->token == DR_LEFT)
	// 	manage_left_redir();
	(*lexer) = (*lexer)->next->next;
}

void
	cmd_parsing_hub(t_mini *s)
{
	t_lexer 	*tmp;

	tmp = s->lexer;
	s->cmd = add_command_back(&s->cmd);

	while (tmp)
	{
		if (tmp->token == ARGS)
			cmd_parsing(s->cmd, &tmp);
		else if (tmp->token == R_RIGHT || tmp->token == R_RIGHT)
			redir_parsing(s->cmd, &tmp);
		// if (tmp->token == PIP)
		// 	s->cmd = add_command_front(&s->cmd);
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
