/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 03:42:20 by imimouni          #+#    #+#             */
/*   Updated: 2023/03/26 06:24:38 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int check_semicolon(char *cmd_line)
{
	int	i;
	int	quotes[2];

	i = 0;
	s_quote = 0;
	d_quote = 0;
    while (cmd_line[i])
	{
        count_quotes(cmd_line[i], &s_quote, &d_quote);
        if (!(s_quote % 2) && !(d_quote % 2))
		{
            if (cmd_line[i] == ';')
			{
				return 1;
            }
        }
		i++;
    }
    return (0);
}

int check_backslash(char *cmd_line)
{
	char *temp;

	temp = ft_strtrim(cmd_line,"'\" ");
	// printf("%c\n\n",cmd_line[ft_strlen(cmd_line) - 1]);
	if ((int)ft_strlen(temp) == 0)
    	return (0);
	if (temp[ft_strlen(temp) - 1] == '\\')
	{
		free(temp);
		return 1;
	}
	free(temp);
    return (0);
}

int	tokens_parssing(char *cmd_line, t_exe *parssing)
{
	if (check_semicolon(cmd_line))
		return (1);
	if (check_quotes(cmd_line))
		return (1);
	if (check_pipes(cmd_line, parssing))
		return (1);
	if (check_redirection(cmd_line))
		return (1);
	if (check_args(cmd_line))
		return (1);
	if (check_backslash(cmd_line))
		return (1);
	// if (parssing->b_parssing)
	// 	return (1);
	
	return (0);
}

void	print_token_name(int code)
{
    if (code == S_QUOTE)
		printf("token->type is S_QUOTE\n");
    else if (code == D_QUOTE)
		printf("token->type is D_QUOTE\n");
    else if (code == N_QUOTE)
		printf("token->type is N_QUOTE\n");
    else if (code == RED_IN)
		printf("token->type is RED_IN\n");
    else if (code == RED_OUT)
		printf("token->type is RED_OUT\n");
    else if (code == RED_IN_D)
		printf("token->type is RED_IN_D\n");
    else if (code == RED_OUT_D)
		printf("token->type is RED_OUT_D\n");
    else if (code == PIPE)
		printf("token->type is PIPE\n");
    else if (code == WORD)
		printf("token->type is WORD\n");
    else
		printf("token->type is Unknown code: %d", code);
}

void	print_token(t_token *token)
{
	while (token)
	{
		// printf("`%s` ", token->value);
		printf("value is `%s`\n", token->value);
		print_token_name(token->type);
		printf("quotes is \"%d\"\n", token->quote);
		printf("space_befor is \"%d\"", token->space_befor);
		// printf("dollar is \"%d\"\n\n", token->dollar);

		token = token->next;
	}
	printf("\n");
}