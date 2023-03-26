/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 03:23:29 by imimouni          #+#    #+#             */
/*   Updated: 2023/03/26 06:24:38 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void ft_token4(int * j, char *cmd_line)
{
	while (cmd_line[(*j)] && ft_isspace(cmd_line[(*j)]))
	{
		(*j)++;
		continue ;
	}
}

void ft_token5(int * j, char *cmd_line)
{
	while (cmd_line[(*j)] && ft_sepa(cmd_line[(*j)]))
	{
		(*j)++;
		continue ;
	}
}

void	remove_quotes2(t_token *token, int *singlequtes)
{
	if ((token->quote == S_QUOTE && (*singlequtes) % 4 == 0) || token->quote == N_QUOTE)
	{
		free(token->value);//
		token->value = ft_strdup2(token->value,'\'');
		free(token->value);//
		token->value = ft_strdup2(token->value,'"');

	}
	else if (token->quote == S_QUOTE)
	{
		free(token->value);//
		token->value = ft_strdup2(token->value,'\'');
	}
	else if (token->quote == D_QUOTE)
	{
		free(token->value);//
		token->value = ft_strdup2(token->value,'"');
	}
	token->type = ft_token_type(token->value);
}

void	remove_quotes(t_token *token, t_exe *parssing)
{
	int	i;
	int	quotes[2];


	(void)parssing;
	while (token)
	{
		ft_quotes_type(token);
		s_quote = 0;
		d_quote = 0;
		i = -1;
		while (token->value[++i] && !ft_isalnum(token->value[i]))
			count_quotes(token->value[i], &s_quote, &d_quote);
		i = ft_strlen(token->value);
		while (token->value[--i] && !ft_isalnum(token->value[i]))
			count_quotes(token->value[i], &s_quote, &d_quote);
		remove_quotes2(token, &s_quote);
		token = token->next;
	}
}

t_token	*ft_token(t_token *token, char *cmd_line, t_exe *err)
{
	int	j;
	int	pos;
	int	quotes[2];
	
	ft_token1(&j , &pos, &s_quote, &d_quote);
	while (cmd_line[j])
	{
		if (ft_token2(&j , cmd_line[j], &s_quote, &d_quote))
			continue ;
		if (!ft_isspace(cmd_line[j]) && !ft_sepa(cmd_line[j]))
		{
			ft_token3(&j , cmd_line, &s_quote, &d_quote);
			ft_add_back(&token, ft_substr(cmd_line, pos, j - pos), err);
			pos = j;
		}
		ft_token4(&j , cmd_line);
		if (ft_sepa(cmd_line[j]))
		{
			ft_token5(&j , cmd_line);
			ft_add_back(&token, ft_substr(cmd_line, pos, j - pos), err);
			pos = j;
		}
	}
	remove_quotes(token, err);//
	return (token);
}
