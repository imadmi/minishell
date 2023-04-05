/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 03:28:35 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/05 07:20:23 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	remove_quotes3(t_token *token)
{
	char	*new_value;

	if (token->type != DOLLAR)
		token->type = WORD;
	if (token->quote == N_QUOTE && token->type != DOLLAR)
	{
		new_value = ft_strdup3(token->value, '"' , '\'');
		free(token->value);
		token->value = new_value;
		token->type = ft_token_type(token->value);
	}
}

void	remove_quotes4(t_token *token)
{
	char	*new_value;

	new_value = ft_strdup(token->value);
	free(token->value);
	token->value = new_value;
	token->type = DOLLAR;
}