/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 03:28:35 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/09 22:04:32 by imimouni         ###   ########.fr       */
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
		new_value = ft_strdup3(token->value, '"', '\'');
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

t_token	*ft_create_new_node(char *value, t_exe *parssing, int space_befor)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
	{
		parssing->b_fail_malloc = 0;
		return (NULL);
	}
	new->value = value;
	new->space_befor = space_befor;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_add_back_suite(t_token **token, char *value, \
t_exe *parssing, int *space_befor)
{
	(*space_befor) = 0;
	if (value[0] == ' ')
		(*space_befor) = 1;
	(*token) = ft_create_new_node(ft_strtrim(value, " "), \
		parssing, *space_befor);
	return ;
}
