/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 03:42:20 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/07 20:37:03 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	check_semicolon(char *cmd_line)
{
	int	i;
	int	quotes[2];

	i = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	while (cmd_line[i])
	{
		count_quotes(cmd_line[i], &quotes[0], &quotes[1]);
		if (!(quotes[0] % 2) && !(quotes[1] % 2))
		{
			if (cmd_line[i] == ';' || cmd_line[i] == '\\')
			{
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	check_backslash(char *cmd_line)
{
	int	i;
	int	quotes[2];

	i = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	char	*temp;

	temp = ft_strtrim(cmd_line, "'\" ");
	if ((int)ft_strlen(temp) == 0)
		return (0);
	while (cmd_line[i])
	{
		count_quotes(cmd_line[i], &quotes[0], &quotes[1]);
		if (!(quotes[0] % 2) && !(quotes[1] % 2))
		{
			if (temp[ft_strlen(temp) - 1] == '\\')
			{
				free(temp);
				return (1);
			}
		}
		i++;
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
	return (0);
}

void	print_token_name(int code)
{
	if (code == S_QUOTE)
		printf("           S_QUOTE\n");
	else if (code == D_QUOTE)
		printf("           D_QUOTE\n");
	else if (code == N_QUOTE)
		printf("           N_QUOTE\n");
	else if (code == RED_IN)
		printf("           RED_IN\n");
	else if (code == RED_OUT)
		printf("           RED_OUT\n");
	else if (code == RED_IN_D)
		printf("           RED_IN_D\n");
	else if (code == RED_OUT_D)
		printf("           RED_OUT_D\n");
	else if (code == PIPE)
		printf("           PIPE\n");
	else if (code == WORD)
		printf("           WORD\n");
	else if (code == FILE)
		printf("           FILE\n");
	else
		printf("Unknown type: %d", code);
}

void	print_token(t_token *token)
{
	while (token)
	{
		printf("value is `%s`\n", token->value);
		print_token_name(token->type);
		printf("quotes is \"%d\"\n", token->quote);
		// printf("space_befor is \"%d\"", token->space_befor);
		token = token->next;
	}
	// printf("\n");
}
