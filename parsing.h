#ifndef PARSING_H
#define PARSING_H

# include <stdio.h>
# include <unistd.h>
#include "./libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

#define S_QUOTE 0
#define D_QUOTE 1
#define RED_IN 2
#define RED_OUT 3
#define RED_IN_D 4
#define RED_OUT_D 5
#define PIPE 6
#define WORD 7
#define N_QUOTE 8


typedef struct		s_exe
{
	int				b_fail_malloc;
	int				b_pipe;
	int				b_parssing;
}					t_exe;

typedef struct s_token
{
	int				space_befor;//
	int				quote;//
	int				type;
	char			*value;
	struct s_token	*next;
	t_exe			*exe;
}					t_token;

#endif 