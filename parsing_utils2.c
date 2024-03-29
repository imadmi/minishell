/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 03:28:05 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/17 03:09:09 by imimouni         ###   ########.fr       */
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
	while (str[i] && j < 9999)
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
	while (str[i] && j < 9999)
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

void	ft_free(t_token *head)
{
	t_token	*current;
	t_token	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->value);
		free(current);
		current = next;
	}
	if (current)
		free(current);
}
