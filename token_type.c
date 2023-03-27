/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 03:21:58 by imimouni          #+#    #+#             */
/*   Updated: 2023/03/27 05:47:10 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	char_quotes_type(char *token)
{
	if (token[ft_strlen(token) - 1] == '\'' && token[0] == '\'')
	{
		return (S_QUOTE);
	}
	if (token[ft_strlen(token) - 1] == '"' && token[0] == '"')
	{
		return (D_QUOTE);
	}
	return (N_QUOTE);
}

void	ft_quotes_type(t_token *token)
{
	if (token->value[ft_strlen(token->value) - 1] == '\'' \
		&& token->value[0] == '\'')
	{
		token->quote = S_QUOTE;
		return ;
	}
	if (token->value[ft_strlen(token->value) - 1] == '"' && \
		token->value[0] == '"')
	{
		token->quote = D_QUOTE;
		return ;
	}
	token->quote = N_QUOTE;
}

int	ft_token_type(char *value)
{
	if (!ft_strcmp(value, "|"))
		return (PIPE);
	else if (!ft_strcmp(value, "<<"))
		return (RED_IN_D);
	else if (!ft_strcmp(value, ">>"))
		return (RED_OUT_D);
	else if (!ft_strcmp(value, "<"))
		return (RED_IN);
	else if (!ft_strcmp(value, ">"))
		return (RED_OUT);
	return (WORD);
}
