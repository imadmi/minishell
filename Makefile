Flags =	-Wall -Wextra -Werror


all: parsing.c parsing.h
	@ cc -fsanitize=address  parsing.c -o minishell
	clear