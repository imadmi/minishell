# FLAGS =	-fsanitize=address
FLAGS =	-Wall -Wextra  -Werror -fsanitize=address
# FLAGS =	-Wall -Wextra  -Werror


all: parsing.c parsing.h
	 cc $(FLAGS) ../libft/libft.a parsing.c\
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
	 tokenizer3.c \
	 expnad.c \
	 expand2.c \
	 expand3.c \
	 expand4.c \
	 remove_quotes.c \
	 token_to_cmd.c \
	 to_cmd_utils.c \
	 -o minishell  -lreadline -ltermcap


#make && sleep 0.1 &&./minishell