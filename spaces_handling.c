/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces_handling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 06:44:23 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/16 01:57:48 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static void	ft_fri(char **sp)
{
	int	i;

	i = 0;
	if (sp == NULL)
		return ;
	while (sp[i] != NULL)
	{
		free(sp[i]);
		i++;
	}
	free(sp);
}

static int	len_arr(char **array)
{
	int	i;

	i = 0;
	if (array == NULL)
		return (0);
	while (array[i] != NULL)
		i++;
	return (i);
}

static void	dollar_nodes_suite(t_token **token, \
t_token **new_node, char **sp, int i)
{
	(*new_node) = malloc(sizeof(t_token));
	(*new_node)->value = ft_strdup(sp[i]);
	(*new_node)->type = DOLLAR;
	(*new_node)->next = (*token)->next;
	if ((*token)->next != NULL)
		(*token)->next->prev = (*new_node);
	(*token)->next = (*new_node);
	(*new_node)->prev = (*token);
}

void	dollar_nodes(t_token *token)
{
	char		**sp;
	t_token		*new_node;
	int			i;

	while (token != NULL)
	{
		if (token->quote == N_QUOTE && token->type == DOLLAR \
			&& ft_strlen(token->value))
		{
			sp = ft_split(token->value, ' ');
			i = len_arr(sp);
			while (--i > 0)
				dollar_nodes_suite(&token, &new_node, sp, i);
			free(token->value);
			token->value = ft_strdup(sp[0]);
			ft_fri(sp);
		}
		token = token->next;
	}
}
