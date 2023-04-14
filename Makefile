# #  "$PWD"' $USER '"$?" $"PWD" $'PWD' '$PWD' "$PWD"

# # while true
# # do leaks minishell
# # sleep 2
# # done

# CFLAGS = -Wall -Werror -Wextra -fsanitize=address
# CFLAGS = -fsanitize=address
# CFLAGS = -Wall -Werror -Wextra

NAME = minishell

CC = gcc

HEADER = parsing.h

SRC = check_token4.c expand_utils.c main.c parsing_utils2.c remove_quotes2.c tokenizer.c check_token.c env.c expand_utils2.c parsing.c to_cmd_utils.c tokenizer2.c check_token2.c expan_char.c expand_utils3.c remove_quote.c token_to_cmd.c tokenizer3.c check_token3.c expand.c parsing_utils.c remove_quotes.c token_type.c tokenizer4.c remove_qts.c

OBJS = $(SRC:.c=.o)

READLINE = -lreadline -ltermcap

all: $(OBJS) $(HEADER)
	@$(CC) $(CFLAGS) $(OBJS) ./libft/libft.a -o $(NAME) $(READLINE)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJS)
	@echo "\033[0;93mobject files removed.\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;93mthe object files and the executable are removed.\033[0m"

re: fclean all

.PHONY: all clean fclean re
