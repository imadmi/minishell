/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 01:14:28 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/12 10:37:11 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include <stdio.h>
# include <unistd.h>
# include "./libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define S_QUOTE 0
# define D_QUOTE 1
# define RED_IN 2
# define RED_OUT 3
# define RED_IN_D 4
# define RED_OUT_D 5
# define PIPE 6
# define WORD 7
# define N_QUOTE 8
# define FILE 9
# define DOLLAR 10

int	g_exit_status;

typedef struct s_red
{
	int				type;
	char			*filename;
	int				quotes;
	struct s_red	*next;
}	t_red;

typedef struct s_cmd
{
	int				n_heredoc;
	int				fd_herdoc;
	char			**args;
	t_red			*red;
	int				pid;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_herdoc
{
	int				fd;
	struct s_herdoc	*next;
}	t_heredoc;

typedef struct s_exe
{
	int				b_fail_malloc;
	int				b_parssing;
}	t_exe;

typedef struct s_token
{
	int				space_befor;
	int				quote;
	int				type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
	t_exe			*exe;
}					t_token;

//env structs

typedef struct s_env
{
	char			*key;
	char			*value;
	int				printed;
	int				equal_c;
	int				visible;
	struct s_env	*next;
	struct s_env	*prev;
}	t_env;

typedef struct s_data
{
	int			should_exit;
	int			shell_level;
	t_env		*env;
	char		**ex_env;
	char		**builtins;
	char		current_dir[1024];
	int			save_stdin;
	int			save_stdout;
	int			fd_in;
	int			fd_out;
	t_token		*head;
	t_heredoc	*her_head;
}	t_data;

char			*env_key(char *str);//
char			*env_value(char *str);//
void			setting_var(char *environ, t_env *tmp);//
void			free_node(t_env *head);//
t_env			*creat_node(void);//
t_env			*export_linked_list(char **environ);//
void			print_env_variables(t_data *data);//
int				setting_data(t_data *data, char **env);//

int				ft_isspace(int c);
int				ft_sepa(char c);
char			*ft_strdup2(char *str, char c);
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strcpy(char *dest, char *src);
void			count_quotes(char c, int *single_quote, int *double_quote);
int				char_quotes_type(char *token);
void			ft_quotes_type(t_token *token);
int				ft_token_type( char *value);
t_token			*ft_create_new_node(char *value, t_exe *parssing, \
int space_befor);
void			ft_add_back(t_token **token, char *value, t_exe *parssing);
void			ft_token1(int *j, int *pos, int *single_quote, \
int *double_quote);
int				ft_token2(int *j, char cmd_line, int *single_quote, \
int *double_quote);
void			ft_token3(int *j, char *cmd_line, int *single_quote, \
int *double_quote);
void			ft_token4(int *j, char *cmd_line);
void			ft_token5(int *j, char *cmd_line);
t_token			*ft_token(t_token *token, char *cmd_line, t_exe *err);
void			remove_quotes(t_token *token, t_exe *parssing);
int				check_pipes_suite2(char *cmd_line);
int				check_pipes_suite(char *cmd_line, int *i, int len);
int				check_pipes(char *cmd_line);
int				check_quotes(char *cmd_line);
int				consecutive_op_redirections_suite(char *cmd_line, int *i, \
char red);
int				consecutive_op_redirections(char *cmd_line, char red);
int				space_between_redirections2(char *cmd_line, int *i, char red, \
int *counter);
int				space_between_redirections(char *cmd_line, char red);
int				consecutive_redirections2(char *cmd_line, char red, int *i, \
int *counter);
int				consecutive_redirections(char *cmd_line, char red);
int				check_redirection(char *cmd_line);
int				check_args2(char *cmd_line, int *i, int *j);
int				check_args(char *cmd_line);
int				check_semicolon(char *cmd_line);
int				check_backslash(char *cmd_line);
int				tokens_parssing(char *cmd_line);
void			print_token_name(int code);
void			print_token(t_token *token);
void			ft_free(t_token *token);
char			*find_env(t_env *env, char *key);
void			remove_quotes3(t_token *token);
char			*ft_strdup3(char *str, char c, char cc);
t_cmd			*ft_parse(char *cmd_line, t_data *data, t_exe *parssin);
void			remove_quotes4(t_token *token);
int				contains_dollar(char *str);
void			remove_quotes2(t_token *token, int *s_q);
void			expand_value_suite(t_env *env, t_token *token);
int				has_dollar_sign(char *s);
void			remove_quotesv3(t_token *token);
void			remove_quotes22(t_token *token, int *s_q);
void			remove_quotesv2(t_token *token);
int				files_type(t_token *token);
void			new_node(t_cmd **cmds, t_cmd **last_cmd, t_cmd **cmdss, \
t_token *token);
int				token_cmd2(t_token **current_token, int *arg_index);
void			add_to_cmd(t_token **current_token, t_cmd **cmd, int \
*arg_index);
void			add_to_cmd2(t_token **current_token, t_cmd **cmd);
void			void_args(t_cmd **cmds, t_cmd **cmd, t_red **red, \
t_cmd	**last_cmd);
t_cmd			*tokens_to_cmds(t_token *token);
void			print_cmds(t_cmd *cmds);
int				nbr_words(t_token *tmp);
int				nbr_herdoc(t_token *tmp);
void			exp_token(t_env *env, t_token *token);
int				tmp_dollar_sign(t_token *token);
int				find_env_check(t_env *env, char *key);
int				ft_isspacee(int c);
int				ft_sepaa(char c);
int				ft_token22(int *j, char cmd_line, int *single_quote, int \
*double_quote);
t_token			*ft_token_exp(t_token *token, char *cmd_line, t_exe *err);
void			expanding_value(t_env *env, t_token *token);
int				ft_sigle_q(t_token *token);
int				ft_skip_red(t_token **token);
char			*join_tokens(t_token *head);
char			*ft_strcat(char *dest, char *src);
void			remove_quotess(char *str);
void			ft_add_back_dol(t_token **token, char *value, t_exe *parssing);
int				contains_only_spaces(char *string);
void			ft_add_back_suite(t_token **token, char *value, \
t_exe *parssing, int *space_befor);
void			ft_add_back_suite_dol(t_token **token, char *value, \
t_exe *parssing, int *space_befor);
int				ft_checker(t_token *tmp);
int				ft_sigle_q2(t_token *token);
int				ft_sigle_q_suite(t_token *token);
int				ft_sigle_q_suitee(t_token *token);
int				ft_sigle_q2e(t_token *token);
int				ft_sigle_qe(t_token *token);
int				ft_isalnumm(int c);
char			*exp_str(t_env *env, char *str);
void			ft_token33(int *j, char *cmd_line);
void			ft_token44(int *j, char *cmd_line);
void			ft_token55(int *j, char *cmd_line);

#endif
