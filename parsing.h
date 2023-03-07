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

#define S_QUOTE 0
#define D_QUOTE 1
#define RED_IN 2
#define RED_OUT 3
#define RED_IN_D 4
#define RED_OUT_D 5
#define PIPE 6
#define WORD 7
#define FILEE 8
// #define CMD 9
// #define ARG 10

typedef struct s_data
{
	char			*cmd_line;
	int				side;
	char			**cmd_sides;
	int				error;
}					t_data;

typedef struct s_token
{
	int				type;
	char			*value;
	// int				sgl_qt;
	// int				args_num;
	// int				redi;
	// int				files;
	// int				count_cmd;
	struct s_token	*next;
}					t_token;

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