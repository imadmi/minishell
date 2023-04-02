/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 01:59:24 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/02 03:04:17 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_parse_tokens(char *cmd_line, t_exe *parssing)
{
	if(!ft_strcmp(cmd_line,""))
		return 0;
	if (tokens_parssing(cmd_line, parssing))
	{
		printf("\033[\033[31;1m× exit\n");
		return (0);
	}
	return (1);
}

t_token	*parssing(char *cmd_line , t_exe *parssing)
{
	t_token	*token;

	token = NULL;
	if (cmd_line)
	{
		if (ft_parse_tokens(cmd_line, parssing))
		{
			parssing->b_parssing = 1;
			token = ft_token(token, cmd_line , parssing);
		}
		else
		{
			parssing->b_parssing = 0;
		}
	}
	return (token);
}

void	exp_token(t_env *env, t_token *token)
{
	while (token != NULL)
	{
		expand_value(env ,token);
		token = token->next;
	}
}

void print_cmds(t_cmd *cmds)
{
	if (cmds == NULL) {
	printf("No commands to print.\n");
	return;
    }
    t_cmd *current_cmd = cmds;

    while (current_cmd != NULL)
	{
        printf("Command:\n");
        printf("  Arguments:\n");
        for (int i = 0; current_cmd->args[i] != NULL; i++)
		{
            printf("    %s\n", current_cmd->args[i]);
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
            current_red = current_red->next;
        }
        current_cmd = current_cmd->next;
    }
}

void files_type(t_token *token)
{
	while(token)
	{
		if (token->type >= RED_IN && token->type <= RED_OUT_D)
			if (token->next)
				token->next->type = FILE;
		token = token->next;
	}
}

t_cmd *new_node(t_cmd **cmds, t_cmd **last_cmd)
{
	t_cmd *cmd = (t_cmd*)malloc(sizeof(t_cmd));
	if (!cmd)
		return NULL;
	cmd->n_heredoc = 0;
	cmd->args = (char**)malloc(sizeof(char*) * MAX_ARGS);
	if (!cmd->args)
	{
		free(cmd);
		return NULL;
	}
	cmd->red = NULL;
	// add command to linked list
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
	return cmd;
}

int token_cmd2(t_token	**current_token, int	*arg_index)
{
	(*arg_index) = 0;
	if ((*current_token)->type == PIPE)
	{
		// skip over the PIPE token
		(*current_token) = (*current_token)->next;
		return 1;
		// continue;
	}
	return 0;
}

void add_to_cmd(t_token	**current_token, t_cmd	**cmd, int	*arg_index)
{
	// add argument to command
	(*cmd)->args[(*arg_index)] = (*current_token)->value;
	(*arg_index)++;
}

t_red *add_to_cmd2(t_token	**current_token, t_cmd	**cmd)
{
	t_red *red;
	t_red *last_red;
	
	red = (t_red*)malloc(sizeof(t_red));
	red->type = (*current_token)->type;
	red->filename = (*current_token)->next->value;
	red->next = NULL;
	// add redirection to command
	if ((*cmd)->red == NULL)
	{
		(*cmd)->red = red;
	}
	else
	{
		last_red = (*cmd)->red;
		while (last_red->next != NULL)
			last_red = last_red->next;
		last_red->next = red;
	}
	// skip over the file token
	(*current_token) = (*current_token)->next;
	return red;
}

t_token *void_args(t_cmd **cmds, t_red **red, t_token *token, t_cmd	**last_cmd)
{
	*cmds = NULL;
	*red = NULL;
	*last_cmd = NULL;
	return (token);
}

t_cmd	*tokens_to_cmds(t_token *token)
{
	t_token	*tmp;
	t_cmd	*cmds;
	t_cmd	*last_cmd;
	int		arg_index;
	t_cmd	*cmd;
	t_red	*red;
	
	tmp = void_args(&cmds, &red, token, &last_cmd);
	while (tmp != NULL)
	{
		if (token_cmd2(&tmp, &arg_index))
			continue ;
		cmd = new_node(&cmds, &last_cmd);
		while (tmp != NULL && tmp->type != PIPE)
		{
			if (tmp->type == WORD)
				add_to_cmd(&tmp, &cmd, &arg_index);	
			else if (tmp->type >= RED_IN && tmp->type <= RED_OUT_D)
				red = add_to_cmd2(&tmp, &cmd);
			tmp = tmp->next;
		}
		cmd->args[arg_index] = NULL;
	}
	return (cmds);
}

t_token	*ft_parse(char *cmd_line, t_data *data, t_exe *parssin, t_cmd	*cmd)
{
	t_token	*token;

	token = parssing(cmd_line ,parssin);
	exp_token(data->env, token);
	files_type(token);
	cmd = tokens_to_cmds(token);
	// print_cmds(cmd);

	return (token);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_exe 		error;
	char		*cmd_line;
	t_cmd		*cmd;
	t_token	 	*token;
	t_data		data;

	if (setting_data(&data, env) != 0)
		return (1);
	cmd = NULL;
	// print_env_variables(&data);//
	printf("\n|***********************************************************|\n");
	printf("|*                                                         *|\n");
	printf("|*                       MINI SHELL                        *|\n");
	printf("|*                   by: Imad && Hatim                     *|\n");
	printf("|*                                                         *|\n");
	printf("|***********************************************************|\n\n");
	while (1)
	{
		// error.b_parssing = 0;
		// error.b_pipe = 0;
		// error.b_fail_malloc = 0;
		cmd_line = readline("\033[1m\033[32m➜ Minishell > \033[0;33m");
		add_history(cmd_line);
		if (!ft_strcmp(cmd_line,"q"))
		{
			printf("\033[\033[31;1m× exit \n");
			clear_history();
			free(cmd_line);
			exit(0);
		}
		if (cmd_line == NULL)
		{
			printf("\033[\033[31;1m× exit \n \033[37;1m");
			free(cmd_line);
			clear_history();
			exit(1);
		}
		token = ft_parse(cmd_line , &data, &error , cmd);
		// print_token(token);//
		if (!ft_strcmp(cmd_line,"clear"))
		{
			system("clear");
		}
		// printf("\nb_parssing %d\n",error.b_parssing);//
		// printf("b_pipe %d\n",error.b_pipe);//
		// printf("b_fail_malloc %d\n",error.b_fail_malloc);//
		free(cmd_line);
		ft_free(token);
		// ft_freee(cmd);
		// system("leaks minishell");
	}
	return (0);
}

		// token = ft_parse(cmd_line ,&error);
