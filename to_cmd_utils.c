/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_cmd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:21:17 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/15 04:49:51 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	exp_token(t_env *env, t_token *token)
{
	t_token	*tmp;
	t_token	*head;

	while (token != NULL)
	{
		tmp = ft_token_exp(NULL, token->value, NULL);
		head = tmp;
		if (token->quote != S_QUOTE && contains_dollar(token->value))
		{
			if (ft_skip_red(&token))
				continue ;
			while (tmp)
			{
				if (tmp_dollar_sign(tmp) && !ft_sigle_q(tmp))
				{
					expanding_value(env, tmp);
				}	
				tmp = tmp->next;
			}
			free(token->value);
			token->value = join_tokens(head, token->quote);
		}
		ft_free(head);
		token = token->next;
	}
}

void	new_node_init(t_cmd **cmd)
{
	(*cmd)->pid = -1;
	(*cmd)->red = NULL;
	(*cmd)->next = NULL;
}

void	new_node(t_cmd **cmds, t_cmd **last_cmd, t_cmd **cmdss, t_token	*token)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return ;
	new_node_init(&cmd);
	cmd->args = (char **)malloc(sizeof(char *) * nbr_words(token));
	if (!cmd->args)
	{
		free(cmd);
		return ;
	}
	if (*cmds == NULL)
	{
		*cmds = cmd;
		*last_cmd = cmd;
	}
	else
	{
		(*last_cmd)->next = cmd;
		*last_cmd = cmd;
	}
	(*cmdss) = cmd;
}
