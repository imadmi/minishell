/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 23:35:52 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/14 02:39:13 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

char	*join_tokens(t_token *head, int quotes)
{
	int			lne;
	char		*result;
	t_token		*tmp;

	tmp = head;
	lne = 0;
	while (tmp != NULL)
	{
		lne += ft_strlen(tmp->value);
		tmp = tmp->next;
	}
	result = (char *)malloc((lne + 1));
	if (result == NULL)
		return (NULL);
	result[0] = '\0';
	tmp = head;
	while (tmp != NULL)
	{
		ft_strcat(result, tmp->value);
		tmp = tmp->next;
	}
	return (remove_quotess(result, quotes));
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
