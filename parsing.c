#include "parsing.h"

int	ft_isspace(int c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int ft_strnncmp(char str1, char str2)
{
	if (str1 != str2)
	{
		return ((str1 < str2) ? -1 : 1);
	}
    return 0;
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

	a = *i + 1;
	b = a;
	while (ft_isspace(cmd_line[b]) && b >= 0)
		b--;
	if (cmd_line[b] == '|' && b >= 0)
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

	b = *i + 1;
	a = b;
	if(!ft_strnncmp('<', red))
		red = '>';
	else if(!ft_strnncmp('>', red))
		red = '<';
	while (a >= 0 && ft_isspace(cmd_line[a]))
		a--;
	if (cmd_line[a] == red)
		return (1);
	a = b + 1;
	while (a < len && ft_isspace(cmd_line[a]))
		a++;
	if (cmd_line[a] == red)
		return (1);
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


int	check_redirection(char *cmd_line)
{
	int	len;
	int	i;
	int	quotes[2];

	i = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	len = ft_strlen(cmd_line);
	// printf("syntax error\n");//
	if (cmd_line[len - 1] == '>' || cmd_line[len - 1] == '<')
	{
		printf("syntax error\n");
		return (1);
	}
	if (consecutive_op_redirections(cmd_line , '>') || consecutive_op_redirections(cmd_line, '<'))
	{
		printf("syntax error\n");
		return (1);
	}
	// if (cmd_line[len - 1] == '>' || cmd_line[len - 1] == '<' || consec_red1(cmd_line)
	// 	|| consec_red2(cmd_line) || space_between_red(cmd_line))
	// 	return (ft_putstr_fd(SNT_ERR, 1), ft_putendl_fd("newline'", 1), 1);
	// if (consec_redin(s) || consec_redout(s))
	// 	return (1);
	return (0);
}

int	tokens_parsing(t_data *data, char *cmd_line)
{
	data->error = 0;
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


t_token	*ft_token(t_token *token, t_data *data, char *cmd_line)
{
	int	i;
	int	start;
	int	side;

	i = 0;
	start = i;
	side = 1;

    // printf("%s\n",cmd_line);//
	nbr_cmd_sides(data, cmd_line);
	data->cmd_sides = ft_split(cmd_line, '|');
    if (cmd_line[0] == '|' || cmd_line[ft_strlen(cmd_line) - 1] == '|')
	{
		printf("unexpected token : `|` \nexit ");
        return (0);
    }
	if (tokens_parsing(data, data->cmd_line))
    {
		printf("exit \n");
		return (0);
    }
	return (token);
	// return (ft_token_side(token, data->cmd_line));
}

void	parsing(t_data data, t_cmd *cmd, t_token *token)
{
    int i = ft_strlen(data.cmd_line);

	if (i)
	{
		token = ft_token(token, &data, data.cmd_line);
		// exp_change_value(envp, token);
		// cmd = node_per_cmd(token);
	}
	// run(data, envp, cmd);
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
		data.cmd_line = readline("$ Minishell > ");
		add_history(data.cmd_line);
		if (data.cmd_line == NULL)
		{
			printf("exit \n");
			exit(0);
		}
        data.cmd_line = ft_strtrim(data.cmd_line, " ");
		parsing(data, cmd, token);
	}
	return (0);
}
