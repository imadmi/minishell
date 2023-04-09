/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 03:39:08 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/09 01:13:15 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	consecutive_redirections2(char *cmd_line, char red, int *i, int *counter)
{
	if (!cmd_line || !i || !counter)
	{
		g_exit_status = 1;
		printf("Error: null pointer detected\n");
		return (1);
	}
	while (cmd_line[*i] && cmd_line[*i + 1] && ft_isspace(cmd_line[*i]))
		(*i)++;
	if (cmd_line[*i] && cmd_line[*i] == red)
		(*counter)++;
	else
		(*counter) = 0;
	if ((*counter) > 2)
	{
		g_exit_status = 258;
		printf("unexpected token \'|\' \n");
		return (1);
	}
	return (0);
}

int	consecutive_redirections(char *cmd_line, char red)
{
	int	i;
	int	quotes[2];
	int	counter;

	quotes[0] = 0;
	quotes[1] = 0;
	counter = 0;
	if (!cmd_line || !red)
		return (printf("Error: null pointer detected\n"));
	i = -1;
	while (cmd_line[++i])
	{
		count_quotes(cmd_line[i], &quotes[0], &quotes[1]);
		if (quotes[0] % 2 || quotes[1] % 2)
		{
			if (cmd_line[i + 1])
				i++;
			continue ;
		}
		if (consecutive_redirections2(cmd_line, red, &i, &counter))
			return (1);
	}
	return (0);
}

int	is_last_char_not_redirect(char *str)
{
	int	i;
	int	quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	i = ft_strlen(str) - 1;
	while (str[i])
	{
		count_quotes(str[i], &quotes[0], &quotes[1]);
		if (quotes[0] % 2 || quotes[1] % 2)
		{
			i--;
			continue ;
		}
		while (i >= 0 && ft_isspace(str[i]))
			i--;
		if (i >= 0 && (str[i] == '<' || str[i] == '>'))
			return (0);
		return (1);
	}
	return (1);
}

int	check_redirection(char *cmd_line)
{
	int	i;

	i = 0;
	if (!is_last_char_not_redirect(cmd_line))
	{
		g_exit_status = 258;
		return (printf("syntax error\n"));
	}
	if (consecutive_redirections(cmd_line, '>') || \
		consecutive_redirections(cmd_line, '<'))
		return (printf("syntax error\n"));
	if (consecutive_op_redirections(cmd_line, '>') || \
		consecutive_op_redirections(cmd_line, '<'))
		return (printf("syntax error\n"));
	if (space_between_redirections(cmd_line, '>') || \
		space_between_redirections(cmd_line, '<'))
		return (printf("syntax error\n"));
	return (0);
}

int	check_args2(char *cmd_line, int *i, int *j)
{
	(*j) = (*i) - 1;
	while (ft_isspace(cmd_line[(*j)]) && (*j) >= 0)
		(*j)--;
	if ((cmd_line[(*j)] == '<' || cmd_line[(*j)] == '>') && (*j) >= 0)
	{
		g_exit_status = 258;
		return (printf("unexpected token \'< or >\' \n"));
	}
	return (0);
}
