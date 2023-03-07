#include "parsing.h"

int	ft_isspace(int c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	is_special(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_isseparator(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (s1 && s2)
	{
		while (s1[i] && s1[i] == s2[i])
			i++;
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (1);
}

int	ft_token_type(char *value)
{
	if (!ft_strcmp(value, "\""))
		return (D_QUOTE);
	else if (!ft_strcmp(value, "'"))
		return (S_QUOTE);
	else if (!ft_strcmp(value, "|"))
		return (PIPE);
	else if (!ft_strcmp(value, "<<"))
		return (RED_IN_D);
	else if (!ft_strcmp(value, ">>"))
		return (RED_OUT_D);
	else if (!ft_strcmp(value, "<"))
		return (RED_IN);
	else if (!ft_strcmp(value, ">"))
		return (RED_OUT);
	return (WORD);
}

// t_token	*ft_create_new_node(char *value)
// {
// 	t_token	*new;

// 	new = (t_token *)malloc(sizeof(t_token));
// 	if (!new)
// 		return (new);
// 	// new->sgl_qt = 0;
// 	// if (value[0] == '\'')
// 	// 	new->sgl_qt = 1;
// 	new->value = value;
// 	new->type = ft_token_type(value);
// 	new->next = NULL;
// 	return (new);
// }

t_token	*ft_create_new_node(char *value)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (new);

	// Allocate memory for value and copy contents of value parameter
	new->value = (char*)malloc((ft_strlen(value) + 1));
	if (!new->value)
	{
		free(new);
		return (NULL);
	}
	strcpy(new->value, value);

	new->type = ft_token_type(value);
	new->next = NULL;
	return (new);
}

// void	ft_add_back(t_token **token, char *value)
// {
// 	t_token	*last;
// 	t_token	*new;

// 	new = ft_create_new_node(ft_strtrim(value, " "));
// 	// new = ft_create_new_node(value);//
// 	if (new == NULL)
// 		return ;
// 	last = *token;
// 	if (last == NULL)
// 	{
// 		*token = new;
// 		return ;
// 	}
// 	while (last->next != NULL)
// 	{
// 		last = last->next;
// 	}
// 	last->next = new;
// }

// void	ft_add_back(t_token **token, char *value)
// {
// 	t_token	*last;
// 	t_token	*new;

void	ft_add_back(t_token **token, char *value)
{
	t_token	*last;
	t_token	*new;

	new = ft_create_new_node(ft_strtrim(value, " "));
	if (new == NULL)
		return ;
	last = *token;
	if (last == NULL)
	{
		*token = new;
		return ;
	}
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new;
}

void	nbr_cmd_sides(t_data *data, char *cmd_line)
{
	int	i;
	int	side;

	i = 0;
	side = 1;
	if (cmd_line == NULL)
        return ;
	while (cmd_line[i])
	{
		if (cmd_line[i] == '|')
        {
			side++;
        }
		i++;
	}
    // printf("%d\n",side);//
	data->side = side;
}

void	count_quotes(char c, int *single_quote, int *double_quote)
{
	if (c == '\'' && (*double_quote) % 2 == 0)
    {
		(*single_quote)++;
    }
	else if (c == '"' && (*single_quote) % 2 == 0)
	{
        (*double_quote)++;
    }
}

int	check_pipes_suite(char *cmd_line, int *i, int len)
{
	int a;
	int	b;

	a = *i;
	b = a - 1;
	while (ft_isspace(cmd_line[b]) && b >= 0)
		b--;
	if (cmd_line[b] == '|' && b >= 0)
	{
		printf("unexpected token `|` \n");
		return 1;
	}	
	b = a + 1;
	while (ft_isspace(cmd_line[b]) && b < len)
		b++;
	if (cmd_line[b] == '|' && b < len)
	{
		printf("unexpected token `|` \n");
		return 1;
	}	
	return (0);
}

int	check_pipes(char *cmd_line)
{
	int	i;
	int	quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	i = 0;
    while (cmd_line[i])
	{
        count_quotes(cmd_line[i], &quotes[0], &quotes[1]);
        if (!(quotes[0] % 2) && !(quotes[1] % 2))
		{
            if (cmd_line[i] == '|')
			{
                if (check_pipes_suite(cmd_line, &i, ft_strlen(cmd_line)))
				{
                    return 1;
                }
            }
        }
		i++;
    }
    return (0);
}

int	check_quotes(char *cmd_line)
{
	int		i;
	int		quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	i = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i] == '\'' && quotes[1] % 2 == 0)
			quotes[0]++;
		else if (cmd_line[i] == '"' && quotes[0] % 2 == 0)
			quotes[1]++;
		i++;
	}
	if (quotes[0] % 2 || quotes[1] % 2)
	{
		printf("Quotes Syntax Error \n");
		return (1);
	}
	return (0);
}

int	consecutive_op_redirections_suite(char *cmd_line, int *i, char red, int len)
{
	int a;
	int b;

	b = *i ;
	a = b -1;
    if (red == '<')
        red = '>';
    else if (red == '>')
        red = '<';
	while (a >= 0 && ft_isspace(cmd_line[a]))
		a--;
	if (a >= 0 && cmd_line[a] == red)
	{
		printf("Error, consecutive redirections \n");
		return (1);
	}
	return (0);
}

int	consecutive_op_redirections(char *cmd_line , char red)
{
	int	i;
	int	quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	i = 0;
	while (cmd_line[i])
	{
		count_quotes(cmd_line[i], &quotes[0], &quotes[1]);
		if (quotes[0] % 2 || quotes[1] % 2)
		{
			i++;
			continue ;
		}
		if (cmd_line[i] == red)
			if (consecutive_op_redirections_suite(cmd_line, &i, red, ft_strlen(cmd_line)))
				return (1);
		i++;
	}
	return (0);
}

int	space_between_redirections(char *cmd_line, char red)
{
	int	counter;
	int	i;

	i = 0;
	while (cmd_line[i])
	{
		counter = 0;
		if (cmd_line[i] == red)
		{
			i++;
			while (cmd_line[i] && ft_isspace(cmd_line[i]))
			{
				i++;
				counter++;
			}
			if (cmd_line[i] == red && counter)
			{
				printf("Error, consecutive redirections \n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	consecutive_redirections(char *cmd_line, char red)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	while (cmd_line[i])
	{
		while (cmd_line[i] && ft_isspace(cmd_line[i]))
			i++;
		if (cmd_line[i] == red)
			counter++;
		else
			counter = 0;
		if (counter > 2)
		{
			printf("Error, consecutive redirections \n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_redirection(char *cmd_line)
{
	int	len;
	int	i;

	i = 0;
	if (cmd_line[ft_strlen(cmd_line) - 1] == '>' || cmd_line[ft_strlen(cmd_line) - 1] == '<')
	{
		printf("syntax error\n");
		return (1);
	}
	if (consecutive_redirections(cmd_line , '>') || consecutive_redirections(cmd_line , '<'))
	{
		printf("syntax error\n");
		return (1);
	}
	if (consecutive_op_redirections(cmd_line , '>') || consecutive_op_redirections(cmd_line, '<'))
	{
		printf("syntax error\n");
		return (1);
	}
	if (space_between_redirections(cmd_line , '>') || space_between_redirections(cmd_line , '<'))
	{
		printf("syntax error\n");
		return (1);
	}
	return (0);
}

int	tokens_parsing(t_data *data, char *cmd_line)
{
	// if (check_pipes(cmd_line) || check_quotes(cmd_line) || check_red(cmd_line) || check_parent(cmd_line))
	if (check_quotes(cmd_line))
	{
		data->error = 1;
		// g_exit_status = 258;
		return (1);
	}
	if (check_pipes(cmd_line))
	{
		data->error = 1;
		// g_exit_status = 258;
		return (1);
	}
	if (check_redirection(cmd_line))
	{
		data->error = 1;
		// g_exit_status = 258;
		return (1);
	}
	return (0);
}

void	print_token(t_token *token)
{
	while (token)
	{
		printf("\ntype is %d\nvalue is \"%s\"\n\n", token->type, token->value);
		token = token->next;
	}
}

void	remove_quotes(t_token *token)
{
	while (token)
	{
		token->value = ft_strtrim(token->value,"\"'");
		token = token->next;
	}
}

t_token	*ft_token(t_token *token, char *cmd_line)
{
	int	j;
	int	position;
	int	quotes[2];
	
	j = 0;
	position = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	while (cmd_line[j])
	{
		count_quotes(cmd_line[j], &quotes[0], &quotes[1]);
		if ((quotes[1] % 2) || (quotes[0] % 2))
			j++;
		if (quotes[1] % 2 || quotes[0] % 2)
			continue ;
		if (!is_isseparator(cmd_line[j]))
		{
			count_quotes(cmd_line[j], &quotes[0], &quotes[1]);
			while ((cmd_line[j] && !is_isseparator(cmd_line[j])) || (cmd_line[j] && (quotes[0] % 2 || quotes[1] % 2)))
			{
				count_quotes(cmd_line[j], &quotes[0], &quotes[1]);
				if (quotes[1] % 2 || quotes[0] % 2)
					j++;
				if (quotes[1] % 2 || quotes[0] % 2)
					continue ;
				j++;
			}
			ft_add_back(&token, ft_substr(cmd_line, position, j - position));
			position = j;
		}
		while (cmd_line[j] && ft_isspace(cmd_line[j]))
			j++;
		if (is_special(cmd_line[j]))
		{
			// printf("*\n");//
			while (cmd_line[j] && is_special(cmd_line[j]))
				j++;
			ft_add_back(&token, ft_substr(cmd_line, position, j - position));
			position = j;
		}
	}
	remove_quotes(token);
	return (token);
	// return (add_file_type(token), remove_quotes(token), token);
}
// t_token	*ft_token(t_token *token, char *cmd_line)
// {
// 	int	j;
// 	int	position;
// 	int	quotes[2];
	
// 	j = 0;
// 	position = 0;
// 	quotes[0] = 0;
// 	quotes[1] = 0;
// 	while (cmd_line[j])
// 	{
// 		count_quotes(cmd_line[j], &quotes[0], &quotes[1]);
// 		if (quotes[1] % 2 || quotes[0] % 2)
// 			j++;
// 		if (quotes[1] % 2 || quotes[0] % 2)
// 			continue ;
// 		if (!is_isseparator(cmd_line[j]))
// 		{
// 			count_quotes(cmd_line[j], &quotes[0], &quotes[1]);
// 			while ((cmd_line[j] && !is_isseparator(cmd_line[j])) || (cmd_line[j] && ((quotes[0]) % 2 || (quotes[1]) % 2)))
// 			{
// 				count_quotes(cmd_line[j], &quotes[0], &quotes[1]);
// 				if (quotes[1] % 2 || quotes[0] % 2)
// 					j++;
// 				if (quotes[1] % 2 || quotes[0] % 2)
// 					continue ;
// 				j++;
// 			}
// 			ft_add_back(&token, ft_substr(cmd_line, position, j - position));
// 			position = j;
// 		}
// 		while (cmd_line[j] && ft_isspace(cmd_line[j]))
// 			j++;
// 		if (is_special(cmd_line[j]))
// 		{
// 			// printf("*\n");//
// 			while (cmd_line[j] && is_special(cmd_line[j]))
// 				j++;
// 			ft_add_back(&token, ft_substr(cmd_line, position, j - position));
// 			position = j;
// 		}
// 	}
// 	remove_quotes(token);
// 	return (token);
// 	// return (add_file_type(token), remove_quotes(token), token);
// }


int ft_parse_tokens(t_token *token, t_data *data, char *cmd_line)
{
	int	i;
	int	start;
	int	side;

	i = 0;
	start = i;
	side = 1;

    // printf("*************************\"%s\"\n",cmd_line);//
	if(!ft_strcmp(cmd_line,""))
		return 0;
	data->error = 0;
	nbr_cmd_sides(data, cmd_line);
	data->cmd_sides = ft_split(cmd_line, '|');
    if (cmd_line[0] == '|' || cmd_line[ft_strlen(cmd_line) - 1] == '|')
	{
		printf("unexpected token : `|` \nexit\n");
        return 0;
    }
	if (tokens_parsing(data, data->cmd_line))
    {
		printf("exit\n");
		return 0;
    }
	return 1;
}

void	parsing(t_data data, t_cmd *cmd, t_token *token)
{
	if (data.cmd_line)
	{
		if (ft_parse_tokens(token, &data, data.cmd_line))
			token = ft_token(token, data.cmd_line);
		else
			token = NULL;
		print_token(token);//

		// exp_change_value(envp, token);
		// cmd = node_per_cmd(token);
	}
	// run(data, envp, cmd);
}

void ft_free(t_token *head)
{
    t_token *temp;

    while (head != NULL)
	{
        temp = head;
        head = head->next;
        free(temp);
    }
}

int	main()
{
	t_data	data;
	t_token	*token;
	t_cmd	*cmd;

	while (1)
	{
		token = NULL;
		cmd = NULL;
		data.cmd_line = readline("\033[0;32m➜ Minishell > \033[0;33m");
		add_history(data.cmd_line);
		if (!ft_strcmp(data.cmd_line,"exit"))
		{
			printf("\033[0;31m➜ exit \n");
			free(data.cmd_line);
			ft_free(token);
			exit(1);
		}
		if (data.cmd_line == NULL)
		{
			printf("\033[0;31m➜ exit \n");
			free(data.cmd_line);
			ft_free(token);
			exit(0);
		}
        // data.cmd_line = ft_strtrim(data.cmd_line, " ");//
		parsing(data, cmd, token);
		free(data.cmd_line);
		ft_free(token);
	}
	return (0);
}
