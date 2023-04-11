/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:17:48 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/11 22:22:40 by imimouni         ###   ########.fr       */
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
				if (!(ft_strcmp(token->next->value, "") == 0))
					token->next->type = FILE;
		token = token->next;
	}
}

int	tmp_dollar_sign(t_token *token)
{
	if (ft_sigle_qe(token))
		return (0);
	if (token->value != '\0' && token->prev)
	{
		while (token->prev)
		{
			if (!token->prev)
				break ;
			if (token->prev)
			{
				if ((ft_strcmp(token->prev->value, "'") == 0 || \
					contains_only_spaces(token->prev->value)))
					token = token->prev;
				else
					break ;
			}
		}
		if (token->prev && token->prev->prev)
			if (ft_strcmp(token->prev->prev->value, "@") == 0)
				return (0);
		if (token->prev)
			if (ft_strcmp(token->prev->value, "$") == 0)
				return (ft_checker(token));
	}
	return (0);
}

void	remove_quotesv3(t_token *token)
{
	char	*new_value;

	if (token->type != DOLLAR)
		token->type = WORD;
	if (token->quote == N_QUOTE)
	{
		new_value = ft_strdup3(token->value, '"', '\'');
		free(token->value);
		token->value = new_value;
		token->type = ft_token_type(token->value);
	}
}

void	remove_quotes22(t_token *token, int *s_q)
{
	char	*new_value;
	int		i;

	i = 0;
	if ((token->quote == S_QUOTE && (*s_q) % 4 == 0))
	{
		new_value = ft_strdup3(token->value, '"', '\'');
		free(token->value);
		token->value = new_value;
		token->quote = D_QUOTE;
		i = 1;
	}
	else if (token->quote == D_QUOTE && i != 1)
	{
		new_value = ft_strdup2(token->value, '"');
		free(token->value);
		token->value = new_value;
	}
	else if (token->quote == S_QUOTE)
	{
		new_value = ft_strdup2(token->value, '\'');
		free(token->value);
		token->value = new_value;
	}
}
