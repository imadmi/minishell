/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:25:42 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/09 22:49:06 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	nbr_words(t_token	*tmp)
{
	t_token	*token;
	int		i;

	token = tmp;
	i = 0;
	while (token != NULL && token->type != PIPE)
	{
		if (token->type == WORD || token->type == DOLLAR)
			i++;
		token = token->next;
	}
	return (i + 1);
}

int	nbr_herdoc(t_token	*tmp)
{
	int		i;
	t_token	*token;

	token = tmp;
	i = 0;
	while (token != NULL && token->type != PIPE)
	{
		if (token->type == RED_IN_D)
			i++;
		token = token->next;
	}
	return (i);
}

int	ft_isspacee(int c)
{
	(void) c;
	return (0);
}

int	ft_sepaa(char c)
{
	if (!ft_isalnum(c) && c != '_')
		return (1);
	if (c == '"' || c == '\'' || c == '$' || c == ' ')
		return (1);
	return (0);
}

int	ft_token22(int *i, char cmd_line, int *single_quote, int *double_quote)
{
	count_quotes(cmd_line, single_quote, double_quote);
	if (((*single_quote) % 2) || ((*double_quote) % 2))
	{
		(*i)++;
		return (1);
	}
	return (0);
}
