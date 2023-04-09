/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:11:05 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/09 21:51:57 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	has_dollar_sign(char *s)
{
	while (*s != '\0')
	{
		if (*s == '$')
			return (1);
		s++;
	}
	return (0);
}

char	*delete_first_char(char *str)
{
	char	*start;

	start = str;
	while (*str != '\0')
	{
		*str = *(str + 1);
		str++;
	}
	return (start + 1);
}

int	ft_checker(t_token *tmp)
{
	char	start[1000];

	ft_strcpy(start, tmp->value);
	if (tmp && tmp->value)
	{
		if (tmp->value[0] <= '9' && tmp->value[0] >= '0')
		{
			free(tmp->value);
			tmp->value = ft_strdup(start + 1);
			free(tmp->prev->value);
			tmp->prev->value = ft_strdup("");
			return (0);
		}
	}
	if (tmp->prev->prev && tmp)
		if (ft_strcmp(tmp->prev->prev->value, "'") == 0 && \
			ft_strcmp(tmp->value, "'") != 0)
			return (1);
	free(tmp->prev->value);
	tmp->prev->value = ft_strdup("");
	return (1);
}

int	contains_only_spaces(char *string)
{
	int	i;

	i = 0;
	while (i < (int)ft_strlen(string))
	{
		if (!ft_isspace(string[i]))
			return (0);
		i++;
	}
	return (1);
}
