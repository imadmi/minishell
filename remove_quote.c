/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 01:20:15 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/11 01:38:46 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_isalnumm(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || (c == '?') || (c == '$'))
		return (1);
	return (0);
}

int	ft_sigle_q_suitee(t_token *token)
{
	if (token->value != '\0' && token->next)
	{
		while (token->next)
		{
			if (!token->next)
				break ;
			if (token->next)
			{
				if (contains_only_spaces(token->next->value))
					token = token->next;
				else
					break ;
			}
		}
		if (token->next)
			if (ft_strcmp(token->next->value, "'") == 0)
				return (1);
	}
	return (0);
}

int	ft_sigle_q2e(t_token *token)
{
	if (token->value != '\0' && token->prev)
	{
		while (token->prev)
		{
			if (!token->prev)
				break ;
			if (token->prev)
			{
				if (contains_only_spaces(token->prev->value) || \
				ft_strcmp(token->prev->value, "$") == 0)
					token = token->prev;
				else
					break ;
			}
		}
		if (token->prev)
			if (ft_strcmp(token->prev->value, "'") == 0)
				return (1);
	}
	return (0);
}

int	ft_sigle_qe(t_token *token)
{
	t_token	*tmp1;
	t_token	*tmp2;

	tmp1 = token;
	tmp2 = token;
	if (ft_sigle_q_suitee(tmp1) && ft_sigle_q2e(tmp2))
		return (1);
	return (0);
}
