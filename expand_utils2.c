/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:29:42 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/12 05:50:10 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_token33(int *j, char *cmd_line)
{
	while ((cmd_line[*j] && !ft_isspacee(cmd_line[*j])
			&& !ft_sepaa(cmd_line[*j])))
	{
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
	int	pos;
	int	i;

	i = 0;
	pos = 0;
	while (cmd_line[i])
	{
		if (!ft_isspacee(cmd_line[i]) && !ft_sepaa(cmd_line[i]))
		{
			ft_token33(&i, cmd_line);
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
