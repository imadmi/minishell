/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_cmd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:21:17 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/10 21:03:42 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	exp_token(t_env *env, t_token *token)
{
	t_token	*tmp;
	t_token	*tmp1;
	t_token	*head;

	while (token != NULL)
	{
		tmp = ft_token_exp(NULL, token->value, NULL);
		head = tmp;
		if (token->quote != S_QUOTE)
		{
			if (ft_skip_red(&token))
				continue ;
			while (tmp)
			{
				tmp1 = tmp;
				if (tmp_dollar_sign(tmp1) && !ft_sigle_q(tmp1))
					expanding_value(env, tmp);
				tmp = tmp->next;
			}
		}
		free(token->value);
		token->value = join_tokens(head);
		ft_free(head);
		token = token->next;
	}
}

void	new_node_init(t_cmd **cmd, t_token	*token)
{
	(*cmd)->pid = -1;
	(*cmd)->n_heredoc = nbr_herdoc(token);
	(*cmd)->red = NULL;
	(*cmd)->next = NULL;
}

void	new_node(t_cmd **cmds, t_cmd **last_cmd, t_cmd **cmdss, t_token	*token)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		return ;
	new_node_init(&cmd, token);
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
