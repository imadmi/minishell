/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expan_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 09:26:39 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/12 09:32:17 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*exp_str(t_env *env, char *str)
{
	t_token	*tmp;
	t_token	*tmp1;
	t_token	*head;
	if (!str)
		return (NULL);
	tmp = ft_token_exp(NULL, str, NULL);
	head = tmp;
	if (contains_dollar(str))
	{
		while (tmp)
		{
			tmp1 = tmp;
			if (tmp_dollar_sign(tmp1))
				expanding_value(env, tmp);
			tmp = tmp->next;
		}
		// free(str);
		str = join_tokens(head);
	}
	ft_free(head);
	return (str);
}
