/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 15:04:38 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/09 21:38:56 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void print_cmds(t_cmd *cmds)
{
	if (cmds == NULL) {
		// printf("No commands to print.\n");
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
		token = token->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_exe 		error;
	char		*cmd_line;
	t_cmd		*cmd;
	t_data		data;

	if (setting_data(&data, env) != 0)
		return (1);
	cmd = NULL;
	while (1)
	{
		cmd_line = readline("➜ Minishell >");
		add_history(cmd_line);
		// if (!ft_strcmp(cmd_line,"q"))
		// {
		// 	printf("\033[\033[31;1m× exit \n");
		// 	clear_history();
		// 	free(cmd_line);
		// 	exit(0);
		// }
		cmd = ft_parse(cmd_line , &data, &error);
		print_cmds(cmd);//
		free(cmd_line);
		// system("leaks minishell");
	}
	return (0);
}