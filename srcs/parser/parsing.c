/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 11:43:00 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/05 17:57:35 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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
