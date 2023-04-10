/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:35:52 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/10 22:50:14 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	remove_quotess(char *str)
{
	int	len;
	int	i;
	int	j;

	len = ft_strlen(str);
	i = 0;
	j = 0;
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

char	*ft_strcat(char *dest, char *src)
{
	char	*dest_end;

	dest_end = dest;
	while (*dest_end != '\0')
		++dest_end;
	while (*src != '\0')
	{
		*dest_end = *src;
		++dest_end;
		++src;
	}
	*dest_end = '\0';
	return (dest);
}

char	*join_tokens(t_token *head)
{
	int			total_length;
	char		*result;
	t_token		*current;

	current = head;
	total_length = 0;
	while (current != NULL)
	{
		total_length += ft_strlen(current->value);
		current = current->next;
	}
	result = (char *)malloc((total_length + 1));
	if (result == NULL)
		return (NULL);
	result[0] = '\0';
	current = head;
	while (current != NULL)
	{
		ft_strcat(result, current->value);
		current = current->next;
	}
	remove_quotess(result);
	return (result);
}

int	ft_sigle_q_suite(t_token *token)
{
	if (token->value != '\0' && token->next)
	{
		while (token->next)
		{
			if (!token->next)
				break ;
			if (token->next)
			{
				if (contains_only_spaces(token->next->value))
					token = token->next;
				else
					break ;
			}
		}
		if (token->next)
			if (ft_strcmp(token->next->value, "'") == 0)
				return (1);
	}
	return (0);
}

int	ft_sigle_q2(t_token *token)
{
	if (token->value != '\0' && token->prev)
	{
		while (token->prev)
		{
			if (!token->prev)
				break ;
			if (token->prev)
			{
				if (contains_only_spaces(token->prev->value))
					token = token->prev;
				else
					break ;
			}
		}
		if (token->prev)
			if (ft_strcmp(token->prev->value, "'") == 0)
				return (1);
	}
	return (0);
}
