/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 03:35:04 by imimouni          #+#    #+#             */
/*   Updated: 2023/03/26 06:24:38 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"


int	check_pipes_suite2(char *cmd_line)
{
	int i;

	i = 0;
	while (ft_isspace(cmd_line[i]) && i < (int)ft_strlen(cmd_line))
		i++;
	if (cmd_line[i] == '|')
	{
		printf("\033[0;31munexpected token \'|\' \n");
		return 1;
	}	
	i = ft_strlen(cmd_line) - 1;
	while (ft_isspace(cmd_line[i]) &&  i > 0)
		i--;
	if (cmd_line[i] == '|')
	{
		printf("\033[0;31munexpected token \'|\' \n");
		return 1;
	}	
	return (0);
}

int	check_pipes_suite(char *cmd_line, int *i, int len)
{
	int a;
	int	b;

	a = *i;
	b = a + 2;
	while (ft_isspace(cmd_line[b]) && b < len)
		b++;
	if (cmd_line[b] == '|' && b < len)
	{
		printf("\033[0;31munexpected token \'|\' \n");
		return 1;
	}	
	return (0);
}

int	check_pipes(char *cmd_line, t_exe *parssing)
{
	int	i;
	int	quotes[2];

	s_quote = 0;
	d_quote = 0;
	i = 0;
    while (cmd_line[i])
	{
        count_quotes(cmd_line[i], &s_quote, &d_quote);
        if (!(s_quote % 2) && !(d_quote % 2))
		{
            if (cmd_line[i] == '|')
			{				
				parssing->b_pipe = 1;
                if (check_pipes_suite2(cmd_line))
                    return 1;
                if (check_pipes_suite(cmd_line, &i, ft_strlen(cmd_line)))
                    return 1;
            }
        }
		i++;
    }
    return (0);
}

int	check_quotes(char *cmd_line)
{
	int		i;
	int		quotes[2];

	s_quote = 0;
	d_quote = 0;
	i = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i] == '\'' && d_quote % 2 == 0)
			s_quote++;
		else if (cmd_line[i] == '"' && s_quote % 2 == 0)
			d_quote++;
		i++;
	}
	if (s_quote % 2 || d_quote % 2)
	{
		printf("Quotes Syntax Error \n");
		return (1);
	}
	return (0);
}