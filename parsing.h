#ifndef PARSING_H
#define PARSING_H
# include <stdio.h>
# include <errno.h>
# include <signal.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/stat.h>
# include <termios.h>
# include <unistd.h>
# include <stdlib.h>
#include "./libft/libft.h"

typedef struct s_exe
{
	int	b_fail_malloc;
	int	b_pipe;
	int	b_parssing;
}	t_exe;

#define S_QUOTE 0
#define D_QUOTE 1
#define RED_IN 2
#define RED_OUT 3
#define RED_IN_D 4
#define RED_OUT_D 5
#define PIPE 6
#define WORD 7

typedef struct s_data
{
	char			*cmd_line;
}					t_data;

typedef struct s_token
{
	int				type;
	char			*value;
	struct s_token	*next;
}					t_token;



#endif 