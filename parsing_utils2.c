/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 03:28:05 by imimouni          #+#    #+#             */
/*   Updated: 2023/03/31 22:30:27 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*ft_strdup2(char *str, char c)
{
	char	temp[10000];
	int		j;
	int		i;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			temp[j] = str[i];
			j++;
		}
		i++;
	}
	temp[j] = '\0';
	return (ft_strdup(temp));
}

char	*ft_strdup3(char *str, char c, char cc)
{
	char	temp[10000];
	int		j;
	int		i;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c && str[i] != cc)
		{
			temp[j] = str[i];
			j++;
		}
		i++;
	}
	temp[j] = '\0';
	return (ft_strdup(temp));
}

void	ft_free(t_token *token)
{
	t_token	*temp;

	while (token != NULL)
	{
		temp = token;
		token = token->next;
		free(temp->value);
		free(temp);
	}
}

void	ft_freee(t_cmd *cmd)
{
	t_cmd	*temp;
	int i = 0;
	while (cmd != NULL)
	{
		while(cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		free(cmd->args);
		while(cmd->red)
		{
			temp->red = cmd->red;
			cmd->red = cmd->red->next;
			free(temp->red);
		}
		temp = cmd;
		cmd = cmd->next;
		free(temp);
	}
}
