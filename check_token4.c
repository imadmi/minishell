/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 03:42:20 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/09 15:07:15 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_semicolon(char *cmd_line)
{
	int	i;
	int	quotes[2];

	i = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	while (cmd_line[i])
	{
		count_quotes(cmd_line[i], &quotes[0], &quotes[1]);
		if (!(quotes[0] % 2) && !(quotes[1] % 2))
		{
			if (cmd_line[i] == ';' || cmd_line[i] == '\\')
			{
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	check_backslash(char *cmd_line)
{
	int		i;
	int		quotes[2];
	char	*temp;

	i = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	temp = ft_strtrim(cmd_line, "'\" ");
	if ((int)ft_strlen(temp) == 0)
		return (0);
	while (cmd_line[i])
	{
		count_quotes(cmd_line[i], &quotes[0], &quotes[1]);
		if (!(quotes[0] % 2) && !(quotes[1] % 2))
		{
			if (temp[ft_strlen(temp) - 1] == '\\')
			{
				free(temp);
				return (1);
			}
		}
		i++;
	}
	free(temp);
	return (0);
}

int	tokens_parssing(char *cmd_line)
{
	if (check_semicolon(cmd_line))
		return (1);
	if (check_quotes(cmd_line))
		return (1);
	if (check_pipes(cmd_line))
		return (1);
	if (check_redirection(cmd_line))
		return (1);
	if (check_args(cmd_line))
		return (1);
	return (0);
}

int	check_args(char *cmd_line)
{
	int	i;
	int	j;
	int	quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	i = -1;
	while (cmd_line[++i])
	{
		count_quotes(cmd_line[i], &quotes[0], &quotes[1]);
		if (quotes[0] % 2 || quotes[1] % 2)
		{
			if (cmd_line [i + 1])
				i++;
			continue ;
		}
		if (cmd_line[i] == '|')
			if (check_args2(cmd_line, &i, &j))
				return (1);
	}
	return (0);
}
