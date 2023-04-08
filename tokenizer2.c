/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 03:23:29 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/08 15:28:18 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_token4(int *j, char *cmd_line)
{
	while (cmd_line[(*j)] && ft_isspace(cmd_line[(*j)]))
	{
		(*j)++;
		continue ;
	}
}

void	ft_token5(int *j, char *cmd_line)
{
	// while (cmd_line[(*j)] && ft_sepa(cmd_line[(*j)]))
	// {
	// 	(*j)++;
	// 	continue ;
	// }
	if (cmd_line[(*j)] && ft_sepa(cmd_line[(*j)]))
	{
		(*j)++;
		// continue ;
	}
}

void	remove_quotes2(t_token *token, int *s_q)
{
	char	*new_value;
	int		i;

	i = 0;
	if ((token->quote == S_QUOTE && (*s_q) % 4 == 0))
	{
		new_value = ft_strdup3(token->value, '"' , '\'');
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
	else if (token->quote == S_QUOTE && token->type != DOLLAR)
	{
		new_value = ft_strdup2(token->value, '\'');
		free(token->value);
		token->value = new_value;
	}
}

int	contains_dollar(char* str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return 1;
		i++;
	}
	return 0;
}

void	remove_quotes(t_token *token, t_exe *parssing)
{
	int	i;
	int	quotes[2];

	(void)parssing;
	while (token)
	{
		if (contains_dollar(token->value))
			remove_quotes4(token);
		ft_quotes_type(token);
		quotes[0] = 0;
		quotes[1] = 0;
		i = 0;
		while (token->value[i] && !ft_isalnum(token->value[i]))
			count_quotes(token->value[i++], &quotes[0], &quotes[1]);
		i = ft_strlen(token->value) - 1;
		while (i >= 0 && !ft_isalnum(token->value[i]))
			count_quotes(token->value[i--], &quotes[0], &quotes[1]);
		remove_quotes2(token, &quotes[0]);
		remove_quotes3(token);
		token = token->next;
	}
}

t_token	*ft_token(t_token *token, char *cmd_line, t_exe *err)
{
	int	quotes[2];
	int	pos;
	int	i;

	ft_token1(&pos, &i, &quotes[0], &quotes[1]);
	while (cmd_line[i])
	{
		if (ft_token2(&i, cmd_line[i], &quotes[0], &quotes[1]))
			continue ;
		if (!ft_isspace(cmd_line[i]) && !ft_sepa(cmd_line[i]))
		{
			ft_token3(&i, cmd_line, &quotes[0], &quotes[1]);
			ft_add_back(&token, ft_substr(cmd_line, pos, i - pos), err);
			pos = i;
		}
		ft_token4(&i, cmd_line);
		if (ft_sepa(cmd_line[i]))
		{
			ft_token5(&i, cmd_line);
			ft_add_back(&token, ft_substr(cmd_line, pos, i - pos), err);
			pos = i;
		}
	}
	remove_quotes(token, err);
	return (token);
}
