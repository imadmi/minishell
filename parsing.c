/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 01:59:24 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/03 03:12:17 by imimouni         ###   ########.fr       */
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
			if (token->next && token->next->type == WORD)
				token->next->type = FILE;
		token = token->next;
	}
}

void	new_node(t_cmd **cmds, t_cmd **last_cmd, t_cmd **cmdss)
{
	t_cmd *cmd = (t_cmd*)malloc(sizeof(t_cmd));
	if (!cmd)
		return ;
	cmd->n_heredoc = 0;
	// cmd->red = (t_red*)malloc(sizeof(t_red*) * MAX_ARGS);
	cmd->args = (char**)malloc(sizeof(char*) * MAX_ARGS);
	if (!cmd->args)
	{
		free(cmd);
		return ;
	}
	cmd->red = NULL;
	cmd->next = NULL;
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

int token_cmd2(t_token	**current_token, int	*arg_index)
{
	(*arg_index) = 0;
	if ((*current_token)->type == PIPE)
	{
		// skip over the PIPE token
		if ((*current_token)->next)
			(*current_token) = (*current_token)->next;
		return 1;
	}
	return 0;
}

void add_to_cmd(t_token	**current_token, t_cmd	**cmd, int	*arg_index)
{
	(*cmd)->args[(*arg_index)] = ft_strdup((*current_token)->value);
	// free((*current_token)->value);
	(*arg_index)++;
}

void	add_to_cmd2(t_token **current_token, t_cmd **cmd)
{
	t_red *temp;
    t_red *red = (t_red*)malloc(sizeof(t_red));
    if (!red)
        return ;
    red->quotes = (*current_token)->quote;
    red->type = (*current_token)->prev->type;
    red->filename = ft_strdup((*current_token)->value);
	// printf("%s : \n" ,red->filename);
    // red->next = NULL;
	red->next = NULL;
    if ((*cmd)->red == NULL)
    {
        (*cmd)->red = red;
		printf("%s\n",(*cmd)->red->filename);
    }
    else
    {
        temp = (*cmd)->red;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = red;
		// red->next = NULL;
		
    }
	// printf("%p\n", &(*cmd)->red);
	// ((*cmd)->red->next) = NULL;
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
	
	cmd = NULL;
	tmp = void_args(&cmds, &red, token, &last_cmd);
	while (tmp != NULL)
	{
		if (token_cmd2(&tmp, &arg_index))
			continue ;
		new_node(&cmds, &last_cmd, &cmd);
		// printf("%p\n", &cmd->red);
		while (tmp != NULL && tmp->type != PIPE)
		{
			if (tmp->type == WORD)
				add_to_cmd(&tmp, &cmd, &arg_index);
			else if (tmp->type == FILE)
				add_to_cmd2(&tmp, &cmd);
			tmp = tmp->next;
		}
		cmd->args[arg_index] = NULL;
	}
	return (cmds);
}

t_cmd	*ft_parse(char *cmd_line, t_data *data, t_exe *parssin)
{
	t_token	*token;
	t_cmd	*cmd;

	cmd = NULL;
	token = parssing(cmd_line ,parssin);
	files_type(token);
	// print_token(token);//
	exp_token(data->env, token);
	cmd = tokens_to_cmds(token);
	// print_cmds(cmd);
	// ft_free(token);

	return (cmd);
}

void free_red(t_red *red)
{
    if (!red)
        return;
    if (red->next)
    	free_red(red->next);
    free(red);
}

void free_cmd(t_cmd *cmd)
{
	int i = 0;
    if (!cmd)
        return;
    if (cmd->args != NULL)
	{
		while(cmd->args[i] != NULL)
			free(cmd->args[i]);
		free(cmd->args);
	}
    if (cmd->red != NULL)
    	free_red(cmd->red);
    if (cmd->next != NULL)
    	free_cmd(cmd->next);
    free(cmd);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_exe 		error;
	char		*cmd_line;
	t_cmd		*cmd;
	// t_token	 	*token;
	t_data		data;

	if (setting_data(&data, env) != 0)
		return (1);
	cmd = NULL;
	while (1)
	{
		cmd = NULL;
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
		cmd = ft_parse(cmd_line , &data, &error);
		print_cmds(cmd);//
		free(cmd_line);
		// free_cmd(cmd);
		// system("leaks minishell");
	}
	return (0);
}

		// token = ft_parse(cmd_line ,&error);
