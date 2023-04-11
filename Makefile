# FLAGS =	-fsanitize=address
FLAGS =	-Wall -Wextra  -Werror -fsanitize=address
# FLAGS =	-Wall -Wextra  -Werror

all: parsing.c parsing.h
	 cc $(FLAGS) ./libft/libft.a \
	 env.c \
	 main.c \
	 \
	 parsing.c\
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
	 tokenizer4.c \
	 expnad.c \
	 expand_utils.c \
	 expand_utils2.c \
	 expand_utils3.c \
	 remove_quotes.c \
	 remove_quotes2.c \
	 token_to_cmd.c \
	 to_cmd_utils.c \
	 remove_quote.c \
	 -o minishell  -lreadline -ltermcap

#make && sleep 0.1 &&./minishell
#  "$PWD"' $USER '"$?" $"PWD" $'PWD' '$PWD' "$PWD"