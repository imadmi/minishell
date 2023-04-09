/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 01:59:24 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/09 01:28:27 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_parse_tokens(char *cmd_line, t_exe *parssing)
{
	if (!ft_strcmp(cmd_line, ""))
		return (0);
	if (tokens_parssing(cmd_line, parssing))
	{
		printf("\033[\033[31;1m× Error\n\033[0;37m");
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
		if (ft_parse_tokens(cmd_line, parssing))
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
	token = parssing(cmd_line, parssin);
	exp_token(data->env, token);
	files_type(token);
	cmd = tokens_to_cmds(token);
	ft_free(token);
	return (cmd);
}
