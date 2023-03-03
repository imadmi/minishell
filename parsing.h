#ifndef PARSING_H
#define PARSING_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "./libft/libft.h"

typedef struct s_struct{
    char *value;
    int type;
    struct s_struct *next;
} t_struct ;

#endif 