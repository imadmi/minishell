/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:18:36 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/16 01:41:22 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	token_cmd2(t_token **current_token, int *arg_index)
{
	(*arg_index) = 0;
	if ((*current_token)->type == PIPE)
	{
		if ((*current_token)->next)
			(*current_token) = (*current_token)->next;
		return (1);
	}
	return (0);
}

void	add_to_cmd(t_token	**current_token, t_cmd	**cmd, int	*arg_index)
{
	(*cmd)->args[(*arg_index)] = ft_strdup((*current_token)->value);
	(*arg_index)++;
	(*cmd)->fd_herdoc = -1;
}

void	add_to_cmd2(t_token **current_token, t_cmd **cmd)
{
	t_red	*temp;
	t_red	*red;

	red = (t_red *)malloc(sizeof(t_red));
	if (!red)
		return ;
	red->quotes = (*current_token)->quote;
	red->type = (*current_token)->prev->type;
	red->filename = ft_strdup((*current_token)->value);
	red->next = NULL;
	if ((*cmd)->red == NULL)
	{
		(*cmd)->red = red;
	}
	else
	{
		temp = (*cmd)->red;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = red;
	}
}

void	void_args(t_cmd **cmds, t_cmd **cmd, t_red **red, t_cmd **last_cmd)
{
	*cmd = NULL;
	*cmds = NULL;
	*red = NULL;
	*last_cmd = NULL;
}

t_cmd	*tokens_to_cmds(t_token *token)
{
	t_cmd	*cmds;
	t_cmd	*last_cmd;
	int		arg_index;
	t_cmd	*cmd;
	t_red	*red;

	void_args(&cmds, &cmd, &red, &last_cmd);
	while (token != NULL)
	{
		if (token_cmd2(&token, &arg_index))
			continue ;
		new_node(&cmds, &last_cmd, &cmd, token);
		while (token != NULL && token->type != PIPE)
		{
			if (token->type == WORD || token->type == DOLLAR)
				add_to_cmd(&token, &cmd, &arg_index);
			else if (token->type == FILE)
				add_to_cmd2(&token, &cmd);
			token = token->next;
		}
		cmd->args[arg_index] = NULL;
	}
	return (cmds);
}
