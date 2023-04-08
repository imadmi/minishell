/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:35:52 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/08 23:38:24 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	remove_quotess(char *str)
{
	int len = ft_strlen(str);
	int i = 0, j = 0;
	while (i < len)
	{
		if (str[i] != '"' && str[i] != '\'')
		{
			str[j] = str[i];
			j++;
		}
		i++;
	}
	str[j] = '\0';
}

char*   ft_strcat(char* dest, const char* src)
{
	char* dest_end = dest;
	while (*dest_end != '\0')
	{
		++dest_end;
	}
	while (*src != '\0')
	{
		*dest_end = *src;
		++dest_end;
		++src;
	}
	*dest_end = '\0';
	return dest;
}

char* join_tokens(t_token* head)
{
	size_t total_length = 0;
	t_token* current = head;
	while (current != NULL)
	{
		total_length += ft_strlen(current->value);
		current = current->next;
	}
	char* result = (char*)malloc((total_length + 1));
	if (result == NULL)
		return NULL;
	result[0] = '\0';
	current = head;
	while (current != NULL)
	{
		ft_strcat(result, current->value);
		current = current->next;
	}
	remove_quotess(result);
	return result;
}

int	ft_sigle_q(t_token *token)
{
	if (token->value != '\0' && token != NULL)
	{
		if (token->prev && token->next)
			if(ft_strcmp(token->next->value,"\"") == 0 && ft_strcmp(token->prev->value,"\"") == 0)
				return 1;
		if (token->prev->prev && token->next)
			if(ft_strcmp(token->next->value,"'") == 0 && ft_strcmp(token->prev->prev->value,"'") == 0)
				return 1;
		if (token->prev && token->next)
			if(ft_strcmp(token->next->value,"'") == 0 && ft_strcmp(token->prev->value,"'") == 0)
				return 1;
	}
	return 0;
}

int  ft_skip_red(t_token **token)
{
	if ((*token)->prev)
	{
		if(ft_strcmp((*token)->prev->value, "<<") == 0)
		{
			printf("*");
			(*token) = (*token)->next;
			return 1;
		}
	}
	return 0;
}
