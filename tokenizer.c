/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 03:22:08 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/10 21:26:55 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_add_back_dol(t_token **token, char *value, t_exe *parssing)
{
	t_token	*last;
	t_token	*new;
	int		space_befor;

	ft_add_back_suite_dol(&new, value, parssing, &space_befor);
	free(value);
	if (new == NULL)
		return ;
	last = *token;
	if (last == NULL)
	{
		*token = new;
		return ;
	}
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new;
	new->prev = last;
}

void	ft_add_back(t_token **token, char *value, t_exe *parssing)
{
	t_token	*last;
	t_token	*new;
	int		space_befor;

	ft_add_back_suite(&new, value, parssing, &space_befor);
	free(value);
	if (new == NULL)
		return ;
	last = *token;
	if (last == NULL)
	{
		*token = new;
		return ;
	}
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new;
	new->prev = last;
}

void	ft_token1(int *pos, int *j, int *single_quote, int *double_quote)
{
	*j = 0;
	*pos = 0;
	*single_quote = 0;
	*double_quote = 0;
}

int	ft_token2(int *j, char cmd_line, int *single_quote, int *double_quote)
{
	count_quotes(cmd_line, single_quote, double_quote);
	if (((*single_quote) % 2) || ((*double_quote) % 2))
	{
		(*j)++;
		return (1);
	}
	return (0);
}

void	ft_token3(int *j, char *cmd_line, int *single_quote, int *double_quote)
{
	count_quotes(cmd_line[*j], single_quote, double_quote);
	while ((cmd_line[*j] && !ft_isspace(cmd_line[*j])
			&& !ft_sepa(cmd_line[*j])) || (cmd_line[*j]
			&& ((*single_quote) % 2 || (*double_quote) % 2)))
	{
		count_quotes(cmd_line[*j], single_quote, double_quote);
		if ((*double_quote) % 2 || (*single_quote) % 2)
			(*j)++;
		if ((*double_quote) % 2 || (*single_quote) % 2)
			continue ;
		(*j)++;
	}
}
