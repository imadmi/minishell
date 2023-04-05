/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 01:59:24 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/05 15:41:26 by imimouni         ###   ########.fr       */
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

int	ft_last_pipe(t_token *token_list)
{
    t_token	*curr;
	
	curr = token_list;
    while (curr->next != NULL)
    {
        curr = curr->next;
    }
    if (curr->type <= PIPE && curr->type >= RED_IN)
    {
		printf("Error\n");
        return 1;
    }
    return 0;
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
			if (ft_last_pipe(token))
			{
				ft_free(token);
				token = NULL;
			}
		}
		else
		{
			parssing->b_parssing = 0;
		}
	}
	return (token);
}

int has_dollar_sign(char* s) {
    while (*s != '\0') {
        if (*s == '$') {
            return 1;
        }
        s++;
    }
    return 0;
}

void	remove_quotesv3(t_token *token)
{
	char	*new_value;

	if (token->type != DOLLAR)
		token->type = WORD;
	if (token->quote == N_QUOTE)
	{
		new_value = ft_strdup3(token->value, '"' , '\'');
		free(token->value);
		token->value = new_value;
		token->type = ft_token_type(token->value);
	}
}

void	remove_quotes22(t_token *token, int *s_q)
{
	char	*new_value;
	int		i;

	i = 0;
	if ((token->quote == S_QUOTE && (*s_q) % 4 == 0))
	{
		new_value = ft_strdup3(token->value, '"' , '\'');
		free(token->value);
		token->value = new_value;
		token->quote = D_QUOTE;
		i = 1;
	}
	else if (token->quote == D_QUOTE && i != 1)
	{
		new_value = ft_strdup2(token->value, '"');
		free(token->value);
		token->value = new_value;
	}
	else if (token->quote == S_QUOTE)
	{
		new_value = ft_strdup2(token->value, '\'');
		free(token->value);
		token->value = new_value;
	}
}

void	remove_quotesv2(t_token *token)
{
	int	i;
	int	quotes[2];

	ft_quotes_type(token);
	quotes[0] = 0;
	quotes[1] = 0;
	i = 0;
	while (token->value[i] && !ft_isalnum(token->value[i]))
		count_quotes(token->value[i++], &quotes[0], &quotes[1]);
	i = ft_strlen(token->value) - 1;
	while (i >= 0 && !ft_isalnum(token->value[i]))
		count_quotes(token->value[i--], &quotes[0], &quotes[1]);
	remove_quotes22(token, &quotes[0]);
	remove_quotesv3(token);
}

void	exp_token(t_env *env, t_token *token)
{
	t_token *tmp;
	char	*str;
	char	**s;
	
	tmp = token;
	while (tmp != NULL)
	{
		if(tmp->quote == D_QUOTE && has_dollar_sign(tmp->value))
			expand_value(env ,tmp);
		else if(tmp->quote == N_QUOTE && has_dollar_sign(tmp->value))
		{
			if (token->prev != NULL)
				if (token->prev->type == RED_IN_D)
				{
					tmp = tmp->next ;
					continue;
				}
		}
		if(has_dollar_sign(tmp->value))
			remove_quotesv2(token);
		tmp = tmp->next;
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
			print_token_name(current_red->type);
			print_token_name(current_red->quotes);
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

int nbr_words(t_token	*tmp)
{
	t_token	*token;

	token = tmp;
	int i = 0;
	while (token != NULL && token->type != PIPE)
	{
		i++;
		token = token->next;
	}
	return (i + 1);
}

void	new_node(t_cmd **cmds, t_cmd **last_cmd, t_cmd **cmdss, t_token	*token)
{
	t_cmd *cmd = (t_cmd*)malloc(sizeof(t_cmd));
	if (!cmd)
		return ;
	cmd->n_heredoc = 0;
	cmd->args = (char**)malloc(sizeof(char*) * nbr_words(token));
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
		if ((*current_token)->next)
			(*current_token) = (*current_token)->next;
		return 1;
	}
	return 0;
}

void add_to_cmd(t_token	**current_token, t_cmd	**cmd, int	*arg_index)
{
	(*cmd)->args[(*arg_index)] = ft_strdup((*current_token)->value);
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
		new_node(&cmds, &last_cmd, &cmd, tmp);
		while (tmp != NULL && tmp->type != PIPE)
		{
			if (tmp->type == WORD || tmp->type == DOLLAR)
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
	exp_token(data->env, token);
	print_token(token);//
	// cmd = tokens_to_cmds(token);
	ft_free(token);

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
		// system(cmd_line);
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
