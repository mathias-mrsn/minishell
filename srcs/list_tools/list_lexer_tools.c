/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_lexer_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamaurai <mamaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 17:53:30 by mamaurai          #+#    #+#             */
/*   Updated: 2022/02/21 11:37:17 by mamaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_lexer
	*create_token(t_quotes	quotes, t_token	token, t_lexer *next, t_lexer *prev)
{
	t_lexer	*lexer;

	lexer = NULL;
	lexer = (t_lexer *)__malloc(sizeof(t_lexer), LEXER_STOCKAGE);
	__bzero(lexer, sizeof(t_lexer));
	lexer->prev = prev;
	lexer->next = next;
	lexer->readed = __FALSE;
	lexer->quotes = quotes;
	lexer->token = token;
	return (lexer);
}

t_boolean
	add_token_back(t_lexer **head, t_quotes quotes, t_token token)
{
	t_lexer	*tmp;

	if (NULL == head)
		return (__FAILURE);
	tmp = (*head);
	if (NULL == tmp)
		(*head) = create_token(quotes, token, NULL, NULL);
	else
	{
		while (NULL != tmp)
		{
			if (NULL == tmp->next)
			{
				tmp->next = create_token(quotes, token, NULL, tmp);
				return (__SUCCESS);
			}
			tmp = tmp->next;
		}
	}
	return (__SUCCESS);
}

t_boolean
	add_token_front(t_lexer **head, t_quotes quotes, t_token token)
{
	t_lexer	*tmp;

	if (NULL == head)
		return (__FAILURE);
	tmp = (*head);
	if (NULL == tmp)
		(*head) = create_token(quotes, token, NULL, NULL);
	else
	{
		(*head) = create_token(quotes, token, tmp, NULL);
	}
	return (__SUCCESS);
}

t_lexer
	*find_last_elem(t_lexer **head)
{
	t_lexer	*tmp;

	tmp = (*head);
	if (NULL == head || NULL == (*head))
		return (NULL);
	while (NULL != tmp)
	{
		if (NULL == tmp->next)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}
