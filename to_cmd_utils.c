/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_cmd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:21:17 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/06 14:23:18 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void print_cmds(t_cmd *cmds)
{
	if (cmds == NULL) {
		printf("No commands to print.\n");
		return;
	}
	
    t_cmd *current_cmd = cmds;
	int i;
	
    while (current_cmd != NULL)
	{
		i = 0;
        printf("Command:\n");
        printf("  Arguments:\n");
        while (current_cmd->args[i] != NULL)
		{
            printf("    %s\n", current_cmd->args[i]);
			i++;
        }
		
		printf("  Redirections:\n");
        t_red *current_red = current_cmd->red;
        while (current_red != NULL)
		{
            switch (current_red->type)
			{
                case RED_IN:
                    printf("    < %s\n", current_red->filename);
                    break;
                case RED_OUT:
                    printf("    > %s\n", current_red->filename);
                    break;
                case RED_IN_D:
                    printf("    << %s\n", current_red->filename);
                    break;
                case RED_OUT_D:
                    printf("    >> %s\n", current_red->filename);
                    break;
                default:
                    break;
            }
			print_token_name(current_red->type);
			print_token_name(current_red->quotes);
            current_red = current_red->next;
        }
		
        current_cmd = current_cmd->next;
    }
}

int nbr_words(t_token	*tmp)
{
	t_token	*token;

	token = tmp;
	int i = 0;
	while (token != NULL && token->type != PIPE)
	{
		if (token->type == WORD || token->type == DOLLAR)
			i++;
		token = token->next;
	}
	return (i + 1);
}

int nbr_herdoc(t_token	*tmp)
{
	t_token	*token;

	token = tmp;
	int i = 0;
	while (token != NULL && token->type != PIPE)
	{
		if (token->type == RED_IN_D)
			i++;
		token = token->next;
	}
	return (i);
}

void	exp_token(t_env *env, t_token *token)
{
	char	*str;
	char	**s;
	
	while (token != NULL)
	{
		if(token->quote == D_QUOTE && has_dollar_sign(token->value))
			expand_value(env ,token);
		else if(token->quote == N_QUOTE && has_dollar_sign(token->value))
		{
			if (token->prev != NULL)
				if (token->prev->type == RED_IN_D)
				{
					token = token->next ;
					continue;
				}
				expand_value2(env, token,str,s);
		}
		if(has_dollar_sign(token->value))
			remove_quotesv2(token);
		token = token->next;
	}
}
