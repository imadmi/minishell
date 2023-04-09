/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 21:43:41 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/09 22:00:55 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_add_back_suite_dol(t_token **token, char *value, \
t_exe *parssing, int *space_befor)
{
	(*space_befor) = 0;
	if (value[0] == ' ')
		(*space_befor) = 1;
	(*token) = ft_create_new_node(ft_strdup(value), parssing, *space_befor);
	return ;
}

int	ft_skip_red(t_token **token)
{
	if ((*token)->prev)
	{
		if (ft_strcmp((*token)->prev->value, "<<") == 0)
		{
			(*token) = (*token)->next;
			return (1);
		}
	}
	return (0);
}
