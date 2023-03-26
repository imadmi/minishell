/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 03:28:05 by imimouni          #+#    #+#             */
/*   Updated: 2023/03/26 06:26:15 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char *ft_strdup2(char *str, char c)
{
	char temp[10000];
	int i = 0;
	int j = 0;
	while(str[i])
	{
		if (str[i] != c)
		{
			temp[j] = str[i];
			j++;
		}
		i++;
	}
	temp[j] = '\0';
	return ft_strdup(temp);
}

void ft_free(t_token *token)
{
    t_token *temp;

    while (token != NULL)
	{
        temp = token;
        token = token->next;
		free(temp->value);
        free(temp);
    }
}
