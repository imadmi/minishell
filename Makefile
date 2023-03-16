# FLAGS =	-fsanitize=addres


all: parsing.c parsing.h
	@ cc $(FLAGS) ./libft/libft.a parsing.c -o minishell  -lreadline -ltermcap