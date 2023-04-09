/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:11:05 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/09 17:29:40 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	has_dollar_sign(char *s)
{
	while (*s != '\0')
	{
		if (*s == '$')
			return (1);
		s++;
	}
	return (0);
}

int	ft_checker(t_token *tmp)
{
	if (tmp->prev->prev && tmp)
		if (ft_strcmp(tmp->prev->prev->value, "'") == 0 && \
			ft_strcmp(tmp->value, "'") != 0)
			return (1);
	free(tmp->prev->value);
	tmp->prev->value = ft_strdup("");
	return (1);
}

int	contains_only_spaces(char* string)
{
    int i = 0;

    while (i < (int)ft_strlen(string))
	{
        if (!ft_isspace(string[i]))
		{
            return 0;
        }
        i++;
    }
    return 1;
}

int	tmp_dollar_sign(t_token *token)
{
	if (token->value != '\0' && token->prev)
	{
		while (token->prev)
		{
			if (!token->prev)
				break ;
			if (token->prev)
			{
				if ((ft_strcmp(token->prev->value, "'") == 0 || \
					contains_only_spaces(token->prev->value) || \
					ft_strcmp(token->prev->value, "\"") == 0))
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
