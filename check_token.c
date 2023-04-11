/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 03:35:04 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/11 19:38:38 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_pipes_suite2(char *cmd_line)
{
	int	i;

	i = 0;
	while (ft_isspace(cmd_line[i]) && i < (int)ft_strlen(cmd_line))
		i++;
	if (cmd_line[i] == '|')
	{
		g_exit_status = 258;
		ft_putstr_fd("unexpected token \'|\' \n", 2);
		return (1);
	}
	i = ft_strlen(cmd_line) - 1;
	while (ft_isspace(cmd_line[i]) && i > 0)
		i--;
	if (cmd_line[i] == '|')
	{
		g_exit_status = 258;
		ft_putstr_fd("unexpected token \'|\' \n", 2);
		return (1);
	}
	return (0);
}

int	check_pipes_suite(char *cmd_line, int *i, int len)
{
	int	a;
	int	b;

	a = *i;
	b = a + 1;
	while (ft_isspace(cmd_line[b]) && b < len)
		b++;
	if (cmd_line[b] == '|' && b < len)
	{
		g_exit_status = 258;
		ft_putstr_fd("unexpected token \'|\' \n", 2);
		return (1);
	}
	return (0);
}

int	check_pipes(char *cmd_line)
{
	int	i;
	int	quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	i = 0;
	while (cmd_line[i])
	{
		count_quotes(cmd_line[i], &quotes[0], &quotes[1]);
		if (!(quotes[0] % 2) && !(quotes[1] % 2))
		{
			if (cmd_line[i] == '|')
			{				
				if (check_pipes_suite2(cmd_line))
					return (1);
				if (check_pipes_suite(cmd_line, &i, ft_strlen(cmd_line)))
					return (1);
			}
		}
		i++;
	}
	return (0);
}

int	check_quotes(char *cmd_line)
{
	int	i;
	int	quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	i = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i] == '\'' && quotes[1] % 2 == 0)
			quotes[0]++;
		else if (cmd_line[i] == '"' && quotes[0] % 2 == 0)
			quotes[1]++;
		i++;
	}
	if (quotes[0] % 2 || quotes[1] % 2)
	{
		ft_putstr_fd("Quotes Syntax Error \n", 2);
		return (1);
	}
	return (0);
}
