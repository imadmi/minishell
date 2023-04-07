/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 01:59:24 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/07 19:59:59 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	ft_parse_tokens(char *cmd_line, t_exe *parssing)
{
	if(!ft_strcmp(cmd_line,""))
		return 0;
	if (tokens_parssing(cmd_line, parssing))
	{
		printf("\033[\033[31;1m× Error\n");
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

t_cmd	*ft_parse(char *cmd_line, t_data *data, t_exe *parssin)
{
	t_token	*token;
	t_cmd	*cmd;

	cmd = NULL;
	token = parssing(cmd_line ,parssin);
	files_type(token);
	exp_token(data->env, token);
	// print_token(token);//
	cmd = tokens_to_cmds(token);
	ft_free(token);

	return (cmd);
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
		// cmd = NULL;
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

// void free_red(t_red *red)
// {
//     if (!red)
//         return;
//     if (red->next)
//     	free_red(red->next);
//     free(red);
// }

// void free_cmd(t_cmd *cmd)
// {
// 	int i = 0;
//     if (!cmd)
//         return;
//     if (cmd->args != NULL)
// 	{
// 		while(cmd->args[i] != NULL)
// 			free(cmd->args[i]);
// 		free(cmd->args);
// 	}
//     if (cmd->red != NULL)
//     	free_red(cmd->red);
//     if (cmd->next != NULL)
//     	free_cmd(cmd->next);
//     free(cmd);
// }