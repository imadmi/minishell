#ifndef PARSING_H
#define PARSING_H
# include <stdio.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/stat.h>
# include <termios.h>
# include <unistd.h>
# include <stdlib.h>
// # include <stdbool.h>
#include "./libft/libft.h"

// # define TRUE 1
// # define FALSE 0

// typedef struct t_list
// {
// 	char	*content;
// 	void	*next;
// }			t_list;

int			g_exit_status;

// typedef struct s_env
// {
// 	char	*name;
// 	char	*value;
// }			t_env;

// typedef enum e_token
// {
// 	S_QUOTE,
// 	D_QUOTE,
// 	RED_IN,
// 	RED_OUT,
// 	RED_IN_APP,
// 	RED_OUT_APP,
// 	PIPE,
// 	FILEE,
// 	WORD,
// 	CMD,
// 	ARG
// }					t_e_token;

typedef struct s_data
{
	char			*cmd_line;
	int				side;
	char			**cmd_sides;
	int				error;
}					t_data;

typedef struct s_tocmd
{
	// char	**args;
	// int		*file_type;
	// char	**file_name;
}			t_tocmd;

typedef struct s_token
{
	// int				type;
	// char			*value;
	// int				sgl_qt;
	// int				args_num;
	// int				redi;
	// int				files;
	// int				count_cmd;
	struct s_token	*next;
}					t_token;

// typedef struct s_files
// {
// 	int				type;
// 	char			*name;
// 	struct s_files	*next;
// }					t_files;

typedef struct s_cmd
{
	// char			**cmd;
	// int				cmdnbr;
	// char			**f_name;
	// int				*f_type;
	// int				fd_out;
	// int				fd_in;
	// char			*findhome;
	// int				cmd_iteration;
	// char			**binfolder;
	// char			*error;
	// int				count_args;
	// int				envvarpos;
	// int				pi[2];
	// char			**splited;
	// int				t;
	// char			**exportnew;

	struct s_cmd	*next;
}					t_cmd;


#endif 