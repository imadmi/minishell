#include "parsing.h"

int ft_parse_tokens(char *cmd_line, t_exe *parssing)
{
	if(!ft_strcmp(cmd_line,""))
		return 0;
	if (tokens_parssing(cmd_line, parssing))
    {
		printf("\033[\033[31;1m× exit\n");
		return 0;
    }
	return 1;
}

t_token *	parssing(char *cmd_line , t_exe *parssing)
{
	t_token *token;

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
	return token  ;
}

void exp_token(t_env *env, t_token *token)
{
    while (token != NULL)
    {
		expand_value(env ,token);
        token = token->next;
    }
}


t_token *ft_parse(char *cmd_line, t_data *data, t_exe *parssin)
{
	t_token *token;

	// token = malloc(sizeof(t_token *));
	// token->next = NULL;
	
	token = parssing(cmd_line ,parssin);
	exp_token(data->env, token);

	// print_token(token);//
	return token;
}



int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_exe 		error;
	char		*cmd_line;
	t_token	 	*token;
	t_data		data;

	if (setting_data(&data, env) != 0)
		return (1);

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
		// parssing.b_pipe = 0;
		// parssing.b_fail_malloc = 0;
		cmd_line = readline("\033[1m\033[32m➜ Minishell > \033[0;33m");
		add_history(cmd_line);
		// printf("%s\n",ft_strchr(cmd_line, '$'));
		if (!ft_strcmp(cmd_line,"q"))
		{
			printf("\033[\033[31;1m× exit \n");
			free(cmd_line);
			clear_history();
			exit(0);
		}
		if (cmd_line == NULL)
		{
			printf("\033[\033[31;1m× exit \n");
			free(cmd_line);
			clear_history();
			exit(1);
		}
		token = ft_parse(cmd_line , &data, &error);
		print_token(token);//
		if (!ft_strcmp(cmd_line,"clear"))
		{
			system("clear");
		}
		// printf("\nb_parssing %d\n",error.b_parssing);//
		// printf("b_pipe %d\n",error.b_pipe);//
		// printf("b_fail_malloc %d\n",error.b_fail_malloc);//
		free(cmd_line);
		ft_free(token);
		// system("leaks minishell");
	}
	return (0);
}

		// token = ft_parse(cmd_line ,&error);
