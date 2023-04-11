/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 01:59:24 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/11 18:04:17 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_sigle_q(t_token *token)
{
	t_token	*tmp1;
	t_token	*tmp2;

	tmp1 = token;
	tmp2 = token;
	if (ft_sigle_q_suite(tmp1) && ft_sigle_q2(tmp2))
		return (1);
	return (0);
}

int	ft_parse_tokens(char *cmd_line)
{
	if (!ft_strcmp(cmd_line, ""))
		return (0);
	if (tokens_parssing(cmd_line))
	{
		write(2, "× Error\n", 9);
		return (0);
	}
	return (1);
}

t_token	*parssing(char *cmd_line, t_exe *parssing)
{
	t_token	*token;

	token = NULL;
	if (cmd_line)
	{
		if (ft_parse_tokens(cmd_line))
			token = ft_token(token, cmd_line, parssing);
		else
		{
			parssing->b_parssing = 1;
		}
	}
	return (token);
}

t_cmd	*ft_parse(char *cmd_line, t_data *data, t_exe *parssin)
{
	t_token	*token;
	t_cmd	*cmd;

	cmd = NULL;
	if (cmd_line)
		if (*cmd_line == '\0')
			return (NULL);
	token = parssing(cmd_line, parssin);
	if (!token)
		return (NULL);
	exp_token(data->env, token);
	files_type(token);
	cmd = tokens_to_cmds(token);
	ft_free(token);
	return (cmd);
}
