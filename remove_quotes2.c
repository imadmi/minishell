/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:17:48 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/09 00:33:54 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	remove_quotesv2(t_token *token)
{
	int	i;
	int	quotes[2];

	ft_quotes_type(token);
	quotes[0] = 0;
	quotes[1] = 0;
	i = 0;
	while (token->value[i] && !ft_isalnum(token->value[i]))
		count_quotes(token->value[i++], &quotes[0], &quotes[1]);
	i = ft_strlen(token->value) - 1;
	while (i >= 0 && !ft_isalnum(token->value[i]))
		count_quotes(token->value[i--], &quotes[0], &quotes[1]);
	remove_quotes22(token, &quotes[0]);
	remove_quotesv3(token);
}

void	files_type(t_token *token)
{
	while (token)
	{
		if (token->type >= RED_IN && token->type <= RED_OUT_D)
			if (token->next && (token->next->type == WORD \
				|| token->next->type == DOLLAR))
				token->next->type = FILE;
		token = token->next;
	}
}
