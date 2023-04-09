/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:29:42 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/09 18:27:28 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_token33(int *j, char *cmd_line, int *single_quote, int *double_quote)
{
	count_quotes(cmd_line[*j], single_quote, double_quote);
	while ((cmd_line[*j] && !ft_isspacee(cmd_line[*j])
			&& !ft_sepaa(cmd_line[*j])) || (cmd_line[*j]
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

void	ft_token44(int *j, char *cmd_line)
{
	while (cmd_line[(*j)] && ft_isspacee(cmd_line[(*j)]))
	{
		(*j)++;
		continue ;
	}
}

void	ft_token55(int *j, char *cmd_line)
{
	if (cmd_line[(*j)] && ft_sepaa(cmd_line[(*j)]))
	{
		(*j)++;
	}
}

t_token	*ft_token_exp(t_token *token, char *cmd_line, t_exe *err)
{
	int	quotes[2];
	int	pos;
	int	i;

	ft_token1(&pos, &i, &quotes[0], &quotes[1]);
	while (cmd_line[i])
	{
		if (!ft_isspacee(cmd_line[i]) && !ft_sepaa(cmd_line[i]))
		{
			ft_token33(&i, cmd_line, &quotes[0], &quotes[1]);
			ft_add_back_dol(&token, ft_substr(cmd_line, pos, i - pos), err);
			pos = i;
		}
		ft_token44(&i, cmd_line);
		if (ft_sepaa(cmd_line[i]))
		{
			ft_token55(&i, cmd_line);
			ft_add_back_dol(&token, ft_substr(cmd_line, pos, i - pos), err);
			pos = i;
		}
	}
	return (token);
}

void delete_and_replace(t_token *token)
{
	char	*key;
    if (token == NULL)
        return ;

	key = token->value;
	free(key);
	token->value = ft_strdup("");
	if (token->prev)
	{
		key = token->prev->value;
		free(key);
		token->prev->value = ft_strdup("");
	}
	return ;
}

void	expanding_value(t_env *env, t_token *token)
{
	char	*str;

	str = token->value;
	if (ft_strcmp(str, "") && str != NULL)
	{
		if (find_env_check(env, str) != 0)
			expand_value_suite(env, token);
		else if (find_env_check(env, str) == 0)
			delete_and_replace(token);
	}
}
