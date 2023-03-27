/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 03:37:07 by imimouni          #+#    #+#             */
/*   Updated: 2023/03/27 02:23:01 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	consecutive_op_redirections_suite(char *cmd_line, int *i, char red)
{
	int	a;

	a = (*i) - 1;
	if (red == '<')
		red = '>';
	else if (red == '>')
		red = '<';
	while (a >= 0 && ft_isspace(cmd_line[a]))
		a--;
	if (a >= 0 && cmd_line[a] == red)
		return (printf("\033[0;31mError, consecutive redirections\n"));
	return (0);
}

int	consecutive_op_redirections(char *cmd_line, char red)
{
	int	i;
	int	quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	i = 0;
	while (cmd_line[i])
	{
		count_quotes(cmd_line[i], &quotes[0], &quotes[1]);
		if (quotes[0] % 2 || quotes[1] % 2)
		{
			i++;
			continue ;
		}
		if (cmd_line[i] == red)
			if (consecutive_op_redirections_suite(cmd_line, &i, red))
				return (1);
		i++;
	}
	return (0);
}

int	space_between_redirections2(char *cmd_line, int *i, char red, int *counter)
{
	(*i)++;
	while (cmd_line[(*i)] && ft_isspace(cmd_line[(*i)]))
	{
		(*i)++;
		(*counter)++;
	}
	if (cmd_line[(*i)] == red && (*counter))
		return (printf("\033[0;31mError, consecutive redirections \n"));
	return (0);
}

int	space_between_redirections(char *cmd_line, char red)
{
	int	i;
	int	quotes[2];
	int	counter;

	quotes[0] = 0;
	quotes[1] = 0;
	i = 0;
	while (cmd_line[i])
	{
		count_quotes(cmd_line[i], &quotes[0], &quotes[1]);
		if (quotes[0] % 2 || quotes[1] % 2)
		{
			i++;
			continue ;
		}
		counter = 0;
		if (cmd_line[i] == red)
			if (space_between_redirections2(cmd_line, &i, red, &counter))
				return (1);
		i++;
	}
	return (0);
}
