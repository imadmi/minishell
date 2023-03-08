FLAGS =	-fsanitize=address


all: parsing.c parsing.h
	@ cc  -g $(FLAGS) ./libft/libft.a parsing.c -o minishell  -lreadline -ltermcap