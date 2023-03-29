FLAGS =	-Wall -Wextra  -Werror -fsanitize=address
# FLAGS =	-Wall -Wextra  -Werror


all: parsing.c parsing.h
	@ cc $(FLAGS) ./libft/libft.a parsing.c\
	 env.c \
	 parsing_utils.c \
	 parsing_utils2.c \
	 check_token.c \
	 check_token2.c \
	 check_token3.c \
	 check_token4.c \
	 token_type.c \
	 tokenizer.c \
	 tokenizer2.c \
	 expnad.c \
	 -o minishell  -lreadline -ltermcap