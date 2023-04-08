/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_cmd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:21:17 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/08 23:37:24 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	exp_token(t_env *env, t_token *token)
{
    t_token *tmp;
    t_token *tmp1;
    t_token *head;

	while (token != NULL)
	{
        tmp = ft_token_exp(NULL, token->value , NULL);
        head = tmp;
        if (ft_skip_red(&token))
            continue;
        while(tmp)
        {
            tmp1 = tmp;
            if (tmp_dollar_sign(tmp1) && !ft_sigle_q(tmp1))
                expanding_value(env ,tmp);
            tmp = tmp->next;
        }
        free(token->value);
        token->value = join_tokens(head);
        ft_free(head);
		token = token->next;
	}
}
