FLAGS =	-Wall -Wextra -Werror


all: parsing.c parsing.h
	@ cc -fsanitize=address $(FLAGS) ./libft/libft.a parsing.c -o minishell
	@ make -C libft
	@ clear