/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_qts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 02:29:01 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/14 02:37:27 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*remove_quotesss(char *str, int quote_type)
{
	char	*temp;

	temp = NULL;
	if (quote_type == D_QUOTE)
	{
		temp = ft_strdup2(str, '"');
		free(str);
	}
	else if (quote_type == S_QUOTE)
	{
		temp = ft_strdup2(str, '\'');
		free(str);
	}
	else if (quote_type == N_QUOTE)
	{
		temp = ft_strdup3(str, '"', '\'');
		free(str);
	}
	if (temp == NULL)
		return (NULL);
	return (temp);
}

char	*remove_quotess(char *str1, int quote_type)
{
	char	*result;

	result = remove_quotesss(str1, quote_type);
	if (result == NULL)
		return (NULL);
	str1 = result;
	return (str1);
}
