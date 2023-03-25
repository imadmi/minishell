#include "parsing.h"

int	ft_isspace(int c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	is_special(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '&' || c == '+')
		return (1);
	return (0);
}

int	is_isseparator(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '&' || c == '+' || c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (s1 && s2)
	{
		while (s1[i] && s1[i] == s2[i])
			i++;
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (1);
}

char	*ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (*(src + i) != '\0')
	{
		*(dest + i) = *(src + i);
		i++;
	}
	dest[i] = '\0';
	return (dest);
}


void	count_quotes(char c, int *single_quote, int *double_quote)
{
	if (c == '\'' && (*double_quote) % 2 == 0)
    {
		(*single_quote)++;
    }
	else if (c == '"' && (*single_quote) % 2 == 0)
	{
        (*double_quote)++;
    }
}

int	char_quotes_type(char *token)
{
	if (token[ft_strlen(token) - 1] == '\'' && token[0] == '\'')
	{
		printf("%c\n",token[0]);
		return S_QUOTE;
	}
	if (token[ft_strlen(token) - 1] == '"' && token[0] == '"')
	{
		return D_QUOTE;
	}
	return N_QUOTE;
}

void	ft_quotes_type(t_token *token)
{
	if (token->value[ft_strlen(token->value) - 1] == '\'' && token->value[0] == '\'')
	{
		token->quote = S_QUOTE;
		return ;
	}
	if (token->value[ft_strlen(token->value) - 1] == '"' && token->value[0] == '"')
	{
		token->quote = D_QUOTE;
		return ;
	}
	token->quote = N_QUOTE;
}

int	ft_token_type( char *value)
{
	// printf("%s\n",value);//
	if (!ft_strcmp(value, "|"))
		return (PIPE);
	else if (!ft_strcmp(value, "<<"))
		return (RED_IN_D);
	else if (!ft_strcmp(value, ">>"))
		return (RED_OUT_D);
	else if (!ft_strcmp(value, "<"))
		return (RED_IN);
	else if (!ft_strcmp(value, ">"))
		return (RED_OUT);
	return (WORD);
}

// t_token	*ft_create_new_node(char *value)
// {
// 	t_token	*new;

// 	new = (t_token *)malloc(sizeof(t_token));
// 	if (!new)
// 		return (new);
// 	// new->sgl_qt = 0;
// 	// if (value[0] == '\'')
// 	// 	new->sgl_qt = 1;
// 	new->value = value;
// 	// new->type = ft_token_type(value);
// 	new->next = NULL;
// 	return (new);
// }

// t_token	*ft_create_new_node(t_token **token, char *value, t_exe *parssing, int space_befor)
// {
// 	t_token	*new;

// 	new = malloc(sizeof(t_token));
// 	if (!new)
// 	{
// 		parssing->b_fail_malloc = 0;
// 		return (NULL);
// 	}

	
// 	// new->value = malloc((ft_strlen(value) + 1));
// 	if (!new->value)
// 	{
// 		parssing->b_fail_malloc = 0;
// 		free(new);
// 		return (NULL);
// 	}
// 	ft_strcpy(new->value, value);
// 	new->space_befor = space_befor;
// 	new->next = NULL;
// 	return (new);
// }

t_token	*ft_create_new_node(char *value, t_exe *parssing, int space_befor)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (!new)
	{
		parssing->b_fail_malloc = 0;
		return (NULL);
	}

	
	new->value = value;
// 	// new->value = malloc((ft_strlen(value) + 1));
	// if (!new->value)
	// {
	// 	parssing->b_fail_malloc = 0;
	// 	free(new);
	// 	return (NULL);
	// }
	// ft_strcpy(new->value, value);
	new->space_befor = space_befor;
	new->next = NULL;
	return (new);
}

void	ft_add_back(t_token **token, char *value, t_exe *parssing)
{
	t_token	*last;
	t_token	*new;
	int space_befor;

	space_befor = 0;
	if (value[0] == ' ')
		space_befor = 1;
	// (*token)->space_befor = 0;
	// if (ft_strlen(ft_strtrim(value, " ")) == 0)
	// 	return;
	new = ft_create_new_node(ft_strtrim(value, " "), parssing, space_befor);
	free(value);
	if (new == NULL)
		return ;
	last = *token;
	if (last == NULL)
	{
		*token = new;
		return ;
	}
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new;
}



int	check_pipes_suite2(char *cmd_line)
{
	int i;

	i = 0;
	while (ft_isspace(cmd_line[i]) && i < (int)ft_strlen(cmd_line))
		i++;
	if (cmd_line[i] == '|')
	{
		printf("\033[0;31munexpected token \'|\' \n");
		return 1;
	}	
	i = ft_strlen(cmd_line) - 1;
	while (ft_isspace(cmd_line[i]) &&  i > 0)
		i--;
	if (cmd_line[i] == '|')
	{
		printf("\033[0;31munexpected token \'|\' \n");
		return 1;
	}	
	return (0);
}

int	check_pipes_suite(char *cmd_line, int *i, int len)
{
	int a;
	int	b;

	a = *i;
	// b = a - 1;
	// while (ft_isspace(cmd_line[b]) && b >= 0)
	// 	b--;
	// if (cmd_line[b] == '|' && b >= 0)
	// {
	// 	// printf("%d\n",b);
	// 	printf("\033[0;31munexpected token \'|\' \n");
	// 	return 1;
	// }
	b = a + 2;
	while (ft_isspace(cmd_line[b]) && b < len)
		b++;
	if (cmd_line[b] == '|' && b < len)
	{
		printf("\033[0;31munexpected token \'|\' \n");
		return 1;
	}	
	return (0);
}

int	check_pipes(char *cmd_line, t_exe *parssing)
{
	// printf("***************");//
	int	i;
	int	quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	i = 0;
    while (cmd_line[i])
	{
        count_quotes(cmd_line[i], &quotes[0], &quotes[1]);
        if (!(quotes[0] % 2) && !(quotes[1] % 2))
		{
            if (cmd_line[i] == '|')
			{				
				parssing->b_pipe = 1;
                if (check_pipes_suite2(cmd_line))
                    return 1;
				// while (ft_isspace(cmd_line[i + 1]) && i < ft_strlen(cmd_line) - 1)
				// 	i++;
				// if (cmd_line[i] == '|')
				// 	return 0;
				// printf("%c\n",cmd_line[0]);
                if (check_pipes_suite(cmd_line, &i, ft_strlen(cmd_line)))
                    return 1;
            }
        }
		i++;
    }
    return (0);
}

int	check_quotes(char *cmd_line)
{
	int		i;
	int		quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	i = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i] == '\'' && quotes[1] % 2 == 0)
			quotes[0]++;
		else if (cmd_line[i] == '"' && quotes[0] % 2 == 0)
			quotes[1]++;
		i++;
	}
	if (quotes[0] % 2 || quotes[1] % 2)
	{
		printf("Quotes Syntax Error \n");
		return (1);
	}
	return (0);
}

int	consecutive_op_redirections_suite(char *cmd_line, int *i, char red)
{
	int a;
	int b;

	b = *i ;
	a = b -1;
	b++;
    if (red == '<')
        red = '>';
    else if (red == '>')
        red = '<';
	while (b < (int)ft_strlen(cmd_line) && ft_isspace(cmd_line[b]))
		b++;
	if (b < (int)ft_strlen(cmd_line) && !ft_isspace(cmd_line[b]))
		return (0);
	while (a >= 0 && ft_isspace(cmd_line[a]))
		a--;
	if (a >= 0 && cmd_line[a] == red)
	{
		printf("\033[0;31mError, consecutive redirections \n");
		return (1);
	}
	return (0);
}

int	consecutive_op_redirections(char *cmd_line , char red)
{
	int	i;
	int	quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	i = 0;
	while (cmd_line[i])
	{
		count_quotes(cmd_line[i], &quotes[0], &quotes[1]);
		if (quotes[0] % 2 || quotes[1] % 2)
		{
			i++;
			continue ;
		}
		if (cmd_line[i] == red)
			if (consecutive_op_redirections_suite(cmd_line, &i, red))
				return (1);
		i++;
	}
	return (0);
}

int	space_between_redirections(char *cmd_line, char red)
{
	int	counter;
	int	i;

	i = 0;
	while (cmd_line[i])
	{
		counter = 0;
		if (cmd_line[i] == red)
		{
			i++;
			while (cmd_line[i] && ft_isspace(cmd_line[i]))
			{
				i++;
				counter++;
			}
			if (cmd_line[i] == red && counter)
			{
				printf("\033[0;31mError, consecutive redirections \n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

int	consecutive_redirections(char *cmd_line, char red)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	while (cmd_line[i])
	{
		while (cmd_line[i] && ft_isspace(cmd_line[i]))
			i++;
		if (cmd_line[i] == red)
			counter++;
		else
			counter = 0;
		if (counter > 2)
		{
			printf("\033[0;31mError, consecutive redirections \n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_redirection(char *cmd_line)
{
	int	i;

	i = 0;
	if (cmd_line[ft_strlen(cmd_line) - 1] == '>' || cmd_line[ft_strlen(cmd_line) - 1] == '<')
	{
		printf("\033[0;31msyntax error\n");
		return (1);
	}
	if (consecutive_redirections(cmd_line , '>') || consecutive_redirections(cmd_line , '<'))
	{
		printf("\033[0;31msyntax error\n");
		return (1);
	}
	if (consecutive_op_redirections(cmd_line , '>') || consecutive_op_redirections(cmd_line, '<'))
	{
		printf("\033[0;31msyntax error\n");
		return (1);
	}
	if (space_between_redirections(cmd_line , '>') || space_between_redirections(cmd_line , '<'))
	{
		printf("\033[0;31msyntax error\n");
		return (1);
	}
	return (0);
}

// int check_args(char *cmd_line)
// {
// 	int	i;
// 	int	quotes[2];

// 	quotes[0] = 0;
// 	quotes[1] = 0;
// 	i = 0;
// 	while (cmd_line[i])
// 	{
// 		count_quotes(cmd_line[i], &quotes[0], &quotes[1]);
// 		if (quotes[0] % 2 || quotes[1] % 2)
// 		{
// 			i++;
// 			continue ;
// 		}
// 		if (cmd_line[i] == '-')
// 			if (ft_isspace(cmd_line[++i]))
// 			{
// 				printf("\033[0;31msyntax error\n");
// 				return (1);
// 			}
// 		i++;
// 	}
// 	return (0);
// }

int check_args(char *cmd_line)
{
	int	i;
	int	j;
	int	quotes[2];

	quotes[0] = 0;
	quotes[1] = 0;
	i = -1;
	while (cmd_line[++i])
	{
		count_quotes(cmd_line[i], &quotes[0], &quotes[1]);
		if (quotes[0] % 2 || quotes[1] % 2)
		{
			i++;
			continue ;
		}
		if (cmd_line[i] == '|')
		{
			j = i - 1;
			i++;
			while(ft_isspace(cmd_line[i]) && cmd_line[i])
				i++;
			if (cmd_line[i] == '<' || cmd_line[i] == '>' || cmd_line[i] == '&')
				return (printf("\033[0;31msyntax error\n"));
			while(ft_isspace(cmd_line[j]) && j >= 0)
				j--;
			if ((cmd_line[j] == '<' || cmd_line[j] == '>'  || cmd_line[j] == '&') && j >= 0)
				return (printf("\033[0;31msyntax error\n"));
		}
	}
	return (0);
}

int check_semicolon(char *cmd_line)
{
	int	i;
	int	quotes[2];

	i = 0;
	quotes[0] = 0;
	quotes[1] = 0;
    while (cmd_line[i])
	{
        count_quotes(cmd_line[i], &quotes[0], &quotes[1]);
        if (!(quotes[0] % 2) && !(quotes[1] % 2))
		{
            if (cmd_line[i] == ';')
			{
				return 1;
            }
        }
		i++;
    }
    return (0);
}

int check_backslash(char *cmd_line)
{
	char *temp;

	temp = ft_strtrim(cmd_line,"'\" ");
	// printf("%c\n\n",cmd_line[ft_strlen(cmd_line) - 1]);
	if ((int)ft_strlen(temp) == 0)
    	return (0);
	if (temp[ft_strlen(temp) - 1] == '\\')
	{
		free(temp);
		return 1;
	}
	free(temp);
    return (0);
}

int	tokens_parssing(char *cmd_line, t_exe *parssing)
{
	if (check_semicolon(cmd_line))
		return (1);
	if (check_quotes(cmd_line))
		return (1);
	if (check_pipes(cmd_line, parssing))
		return (1);
	if (check_redirection(cmd_line))
		return (1);
	if (check_args(cmd_line))
		return (1);
	if (check_backslash(cmd_line))
		return (1);
	// if (parssing->b_parssing)
	// 	return (1);
	
	return (0);
}

void	print_token_name(int code)
{
    if (code == S_QUOTE)
		printf("token->type is S_QUOTE\n");
    else if (code == D_QUOTE)
		printf("token->type is D_QUOTE\n");
    else if (code == N_QUOTE)
		printf("token->type is N_QUOTE\n");
    else if (code == RED_IN)
		printf("token->type is RED_IN\n");
    else if (code == RED_OUT)
		printf("token->type is RED_OUT\n");
    else if (code == RED_IN_D)
		printf("token->type is RED_IN_D\n");
    else if (code == RED_OUT_D)
		printf("token->type is RED_OUT_D\n");
    else if (code == PIPE)
		printf("token->type is PIPE\n");
    else if (code == WORD)
		printf("token->type is WORD\n");
    else
		printf("token->type is Unknown code: %d", code);
}

void	print_token(t_token *token)
{
	while (token)
	{
		// printf("`%s` ", token->value);
		printf("value is `%s`\n", token->value);
		print_token_name(token->type);
		printf("quotes is \"%d\"\n", token->quote);
		printf("space_befor is \"%d\"", token->space_befor);
		// printf("dollar is \"%d\"\n\n", token->dollar);

		token = token->next;
	}
	printf("\n");
}

char	*ft_str_chr(char *str, char c)
{
	int	i;

	i = ft_strlen(str);
	while (i < ft_strlen(str) - 1)
	{
		if (str[i] == c)
			return ((char *)str + i);
		i++;
	}
	return (NULL);
}

// char* ft_strncpy(char* dest, const char* src, size_t n)
// {
//     size_t i = 0;
//     while (i < n && src[i] != '\0') {
//         dest[i] = src[i];
//         i++;
//     }
//     while (i < n) {
//         dest[i] = '\0';
//         i++;
//     }
//     return dest;
// }

// char* remove_f_l(char *str)
// {
// 	int len = ft_strlen(str);
// 	char* newStr = (char*) malloc(len - 1);

// 	ft_strncpy(newStr, str + 1, len - 2);
// 	newStr[len - 2] = '\0';

// 	return newStr;
// }

// void remove_s_quotes_suit(char **str, int *i)
// {
//     char *newStr = remove_f_l(*str);
//     if (newStr[0] == '\'' && newStr[strlen(newStr) - 1] == '\'')
//     {
//         (*i)++;
//         remove_s_quotes_suit(&newStr, i);
//     }
//     *str = newStr;
// }

// void remove_d_quotes_suit(char **str)
// {
//     char *newStr = remove_f_l(*str);
//     if (newStr[0] == '"' && newStr[strlen(newStr) - 1] == '"')
//     {
//         remove_d_quotes_suit(&newStr);
//     }
//     *str = newStr;
// }

// char *trim_quote(char const *s1, char set)
// {
//     size_t len = strlen(s1);
//     char *result = malloc(len + 1);
//     size_t j = 0;

//     for (size_t i = 0; i < len; i++) {
//         if (s1[i] != set) {
//             result[j] = s1[i];
//             j++;
//         }
//     }
//     result[j] = '\0';

//     return result;
// }

char *ft_strdup2(char *str, char c)
{
	char temp[10000];
	int i = 0;
	int j = 0;
	while(str[i])
	{
		if (str[i] != c)
		{
			temp[j] = str[i];
			j++;
		}
		i++;
	}
	temp[j] = '\0';
	return ft_strdup(temp);
}

void	remove_quotes(t_token *token, t_exe *parssing)
{
	int	i;
	int	quotes[2];


	(void)parssing;
	while (token)
	{
		ft_quotes_type(token);
		quotes[0] = 0;
		quotes[1] = 0;
		i = -1;
		while (token->value[++i] && !ft_isalnum(token->value[i]))
			count_quotes(token->value[i], &quotes[0], &quotes[1]);
		i = ft_strlen(token->value);
		while (token->value[--i] && !ft_isalnum(token->value[i]))
			count_quotes(token->value[i], &quotes[0], &quotes[1]);
		if ((token->quote == S_QUOTE && quotes[0] % 4 == 0) || token->quote == N_QUOTE)
		{
			free(token->value);//
			token->value = ft_strdup2(token->value,'\'');
			free(token->value);//
			token->value = ft_strdup2(token->value,'"');

		}
		else if (token->quote == S_QUOTE)
		{
			free(token->value);//
			token->value = ft_strdup2(token->value,'\'');
		}
		else if (token->quote == D_QUOTE)
		{
			free(token->value);//
			token->value = ft_strdup2(token->value,'"');
		}
		token->type = ft_token_type(token->value);
		token = token->next;
	}
}

t_token	*ft_token(t_token *token, char *cmd_line, t_exe *parssing)
{
	int	j;
	int	position;
	int	quotes[2];
	
	j = 0;
	position = 0;
	quotes[0] = 0;
	quotes[1] = 0;
	while (cmd_line[j])
	{
		count_quotes(cmd_line[j], &quotes[0], &quotes[1]);
		if ((quotes[1] % 2) || (quotes[0] % 2))
		{
			j++;
			continue ;
		}
		if (!is_isseparator(cmd_line[j]))
		{
			count_quotes(cmd_line[j], &quotes[0], &quotes[1]);
			// while ((cmd_line[j] && !is_isseparator(cmd_line[j])))
			while ((cmd_line[j] && !is_isseparator(cmd_line[j])) || (cmd_line[j] && (quotes[0] % 2 || quotes[1] % 2)))
			{
				count_quotes(cmd_line[j], &quotes[0], &quotes[1]);
				if ((quotes[1] % 2) || (quotes[0] % 2))
				{
					j++;
					continue ;
				}
				j++;
			}
			// printf("`%s`\n",ft_substr(cmd_line, position, j - position));//
			ft_add_back(&token, ft_substr(cmd_line, position, j - position), parssing);
			position = j;
		}
		while (cmd_line[j] && ft_isspace(cmd_line[j]))
		{
			j++;
			continue ;
		}
		if (is_special(cmd_line[j]))
		{
			// printf("*\n");//
			while (cmd_line[j] && is_special(cmd_line[j]))
				j++;
			// printf("`%s`\n",ft_substr(cmd_line, position, j - position));//
			ft_add_back(&token, ft_substr(cmd_line, position, j - position), parssing);
			position = j;
		}
	}
	remove_quotes(token, parssing);//
	return (token);
}

int ft_parse_tokens(t_token *token, char *cmd_line, t_exe *parssing)
{
	int	i;
	int	start;
	int	side;

	i = 0;
	start = i;
	side = 1;

	(void)token;
	if(!ft_strcmp(cmd_line,""))
		return 0;
	if (tokens_parssing(cmd_line, parssing))
    {
		printf("\033[\033[31;1m× exit\n");
		return 0;
    }
	return 1;
}

void ft_free(t_token *token)
{
    t_token *temp;

    while (token != NULL)
	{
        temp = token;
        token = token->next;
		free(temp->value);
        free(temp);
    }
}

// void ft_dollar(t_token *token)//
// {
//     while (token != NULL)
// 	{
// 		if (token->value[ft_strlen(token->value) - 1] == '$' && token->next->next != NULL)
// 		{
// 			if ((token->next->value[0] == '(' || token->next->value[0] == '{')\
// 				&& (token->next->next->next->value[0] == ')' || token->next->next->next->value[0] == '}'))
// 			{
// 				token->dollar = 2;

// 				char *temp = ft_strtrim(token->value,"$");
// 				free(token->value);
// 				token->value = temp;

				
// 				t_token *tmp;
// 				tmp = token->next;
// 				token->next = token->next->next;
// 				free(tmp->value);
// 				free(tmp);

// 				token = token->next;
// 				token->dollar = 1; 

// 				tmp = token->next;
// 				token->next = token->next->next;
// 				free(tmp->value);
// 				free(tmp);
// 			}
// 		}
//         token = token->next;
//     }
// }

t_token *	parssing(char *cmd_line , t_exe *parssing)
{
	t_token *token;

	// token = NULL;//
	if (cmd_line)
	{
		if (ft_parse_tokens(token, cmd_line, parssing))
		{
			parssing->b_parssing = 1;
			// printf("%d\n",parssing->b_parssing);
			// token = NULL;
			token = ft_token(NULL, cmd_line , parssing);
			// ft_dollar(token);
			// print_token(token);
			// counter = 1;
			// if (!parssing->b_parssing)
			// 	ft_parse_tokens(token, cmd_line, parssing, counter);
			// // print_token(token);//
			// // ft_free(token);
		}
		else
		{
			token = NULL;
			parssing->b_parssing = 0;
			// printf("%d\n",parssing->b_parssing);
		}
	}
	return token  ;
}

// int	dolar_exist(char *s)
// {
// 	int	i;

// 	i = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '$')
// 			return (i);
// 		i++;
// 	}
// 	return (-1);
// }


char  *find_env(t_env *env, char *key)
{
    while (env != NULL)
    {
        if (ft_strcmp(env->key, key) == 0)
        {
            return env->value;
        }
        env = env->next;
    }
    return NULL;
}

char	*ft_strchr2(char *s, int c, int *flag)
{
	int	i;
	int	quotes[2];

	i = ft_strlen(s);
	char *res;
	quotes[0] = 0;
	quotes[1] = 0;
	while (s[--i] && !ft_isalnum(s[i]))
	{
		count_quotes(s[i], &quotes[0], &quotes[1]);
	}
	if (quotes[0] == 1)
		(*flag) = 1;
	i = -1;
	while (s[++i])
	{
		if (s[i] == (char)c)
		{
			res = ft_strtrim(((char *)s + i), "'$");
			return res;
		}
	}
	return (NULL);
}

void expand_value(t_env *env, t_token *token)
{
	if(ft_strchr(token->value, '$') && token->quote != S_QUOTE)
	{
		int i = 0;
		int flag = 0;
		while(token->value[i])
		{
			if (token->value[i] == '$')
			{
				char *str;
				
				str = ft_strchr2(token->value, '$', &flag);
				// if (find_env(env, ft_strchr(token->value, '$') + 1) != NULL)
				if (find_env(env, str) != NULL)
				{
					char *key;
					key = ft_strtrim(ft_strchr(token->value, '$'), "$'");
					char suff[i + ft_strlen(find_env(env, key))] ;
					ft_strlcpy(suff, token->value, i + 1);
					ft_strlcat(suff, find_env(env, key),ft_strlen(find_env(env, key)) + i + 1);
					if (flag)
						ft_strlcat(suff, "'", ft_strlen(find_env(env, key)) + i + 1 + 1);/////
					// char *value = token->value;
					free(token->value);
					token->value = ft_strdup(suff);
					// printf("%s\n",find_env(env, key));
					free(key);
				}
				free(str);
			}
			i++;
		}
	}
}

int contains_dollar(char *str)
{
	int i = 0;
	while(str[i])
	{
		if (str[i] == '$')
			return 1;
		i++;
	}
    return 0;
}

// int exp_valuebrackets(t_env *env ,t_token *token)
// {
// 	if ((token->dollar == 1  && token->quote == N_QUOTE) || contains_dollar(token->value))
// 	{
// 		// printf("%d\n\n",token->dollar);
// 		char *key = ft_strtrim(token->value,"$\"({}) ");

// 		if (find_env(env, key) != NULL)
// 		{
// 			// char *value = token->value;
// 			free(token->value);
// 			token->value = ft_strdup(find_env(env, key));
// 			// printf("%s\n",find_env(env, key));
// 		}
// 		free(key);
// 		return 1;
// 	}
// 	return 0;
// }
// int exp_valuebrackets(t_env *env ,t_token *token)
// {
// 	if(ft_strchr(token->value, '$'))
// 	{
// 		char *key = ft_strtrim(token->value, "${}");

// 		if (find_env(env, key) != NULL)
// 		{
// 			// char *value = token->value;
// 			free(token->value);
// 			token->value = ft_strtrim(find_env(env, key),"");
// 			// printf("%s\n",find_env(env, key));
// 		}
// 		free(key);
// 	}
// 	return 0;
// }


// void exp_valuebrackets2(t_env *env ,t_token *token)
// {

// 	int	i;
// 	int	quotes[2];

// 	quotes[0] = 0;
// 	quotes[1] = 0;
// 	i = 0;
//     while (token->value[i])
// 	{
//         count_quotes(token->value[i], &quotes[0], &quotes[1]);
//         if ((quotes[0] == 0) && !(quotes[1] % 2) )
// 		{
// 			char *key = ft_strtrim(token->value, "$()\"");

// 			if (find_env(env, key) != NULL)
// 			{
// 				// char *value = token->value;
// 				free(token->value);
// 				token->value = ft_strtrim(find_env(env, key),"");
// 				// printf("%s\n",find_env(env, key));
// 			}
// 			free(key);
//         }
// 		i++;
//     }
// }

void exp_value(t_env *env, t_token *token)
{
    while (token != NULL)
    {
		expand_value(env ,token);
		// if (expand_value(env ,token))
		// {
		// 	token = token->next;
		// 	continue;
		// }
		// else if (exp_valuebrackets(env ,token))
		// {
		// 	// ft_delete(token);
		// 	// printf("\n\n'%s'\n\n",token->value);
		// 	token = token->next;
		// 	continue;
		// }
		// else if (contains_dollar(token->value))
		// {
		// 	// token = ft_token(NULL, token->value , NULL);
		// 	// exp_value(env, token);
		// 	// ft_delete(token);
		// 	token = token->next;
		// 	continue;
		// }
        token = token->next;
    }
}


t_token *ft_parse(char *cmd_line, t_data *data, t_exe *parssin)
{
	t_token *token;

	// token = malloc(sizeof(t_token *));
	// token->next = NULL;
	
	token = parssing(cmd_line ,parssin);
	exp_value(data->env, token);

	// print_token(token);//
	return token;
}

char	*env_key(char *str)
{
	int		i;
	char	*p;

	i = 0;
	while (str[i] != '=' && str[i])
		i++;
	p = malloc(i + 1);
	if (!p)
		return (NULL);
	i = 0;
	while (str[i] != '=')
	{
		p[i] = str[i];
		i++;
	}
	return (p[i] = '\0', p);
}

char	*env_value(char *str)
{
	int		i;
	char	*p;
	int		j;

	j = 0;
	i = 0;
	while (*str != '=')
		str++;
	if (*str)
		str++;
	while (str[i])
		i++;
	p = malloc(i + 1);
	i = 0;
	if (!p)
		return (NULL);
	while (str[i])
		p[j++] = str[i++];
	return (p[j] = '\0', p);
}

void	setting_var(char *environ, t_env *tmp)
{
	tmp->key = env_key(environ);
	tmp->value = env_value(environ);
}

void	free_node(t_env *head)
{
	t_env	*tmp;

	while (head)
    {
		tmp = head;
		if (head->key)
			free(head->key);
		if (head->value)
			free(head->value);
		head = head->next;
		free(tmp);
	}
	exit(1);
}

t_env	*creat_node(void)
{
	t_env	*p;

	p = malloc(sizeof(t_env));
	if (!p)
		return (NULL);
	p->key = NULL;
	p->value = NULL;
	return (p);
}

t_env	*export_linked_list(char **environ)
{
	int		i;
	t_env	*head;
	t_env	*tmp;

	i = 0;
	head = creat_node();
	if (head == NULL)
		exit(1);
	head->key = env_key(environ[i]);
	if (!head->key)
		exit(1);
	head->value = env_value(environ[i]);
	head->equal_c = 1;
	i++;
	head->printed = -1;
	tmp = head;
	while (environ[i])
	{
		tmp->next = creat_node();
		if (tmp->next == NULL)
			free_node(head);
		tmp = tmp->next;
		setting_var(environ[i], tmp);
		tmp->equal_c = 1;
		if (!tmp->key || !tmp->value)
			return (tmp->next = NULL, free_node(head), NULL);
		tmp->printed = -1;
		i++;
	}
	return (tmp->next = NULL, head);
}

void print_env_variables(t_data *data)
{
    t_env *env = data->env;
    while (env)
    {
        printf("%s=%s\n", env->key, env->value);
        env = env->next;
    }
}

int	setting_data(t_data *data, char **env)
{
	data->env = export_linked_list(env);
	data->shell_level = 1;
	if (!data->env)
		return (1);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	t_exe 		error;
	char		*cmd_line;
	t_token	 	*token;
	t_data		data;

	if (setting_data(&data, env) != 0)
		return (1);

	// print_env_variables(&data);//

	// system("clear");//
	printf("\n|***********************************************************|\n");
	printf("|*                                                         *|\n");
	printf("|*                       MINI SHELL                        *|\n");
	printf("|*                   by: Imad && Hatim                     *|\n");
	printf("|*                                                         *|\n");
	printf("|***********************************************************|\n\n");
	while (1)
	{
		// token = NULL;
		error.b_parssing = 0;
		// parssing.b_pipe = 0;
		// parssing.b_fail_malloc = 0;
		cmd_line = readline("\033[1m\033[32m➜ Minishell > \033[0;33m");
		add_history(cmd_line);
		// printf("%s\n",ft_strchr(cmd_line, '$'));
		if (!ft_strcmp(cmd_line,"q"))
		{
			printf("\033[\033[31;1m× exit \n");
			free(cmd_line);
			// ft_free(token);
			clear_history();
			exit(0);
		}
		if (cmd_line == NULL)
		{
			printf("\033[\033[31;1m× exit \n");
			free(cmd_line);
			// ft_free(token);
			clear_history();
			exit(1);
		}
		token = ft_parse(cmd_line , &data, &error);
		// while (token)
		// {
		// 	printf("%s\n",token->value);
		// 	token = token->next;
		// }
		
		print_token(token);//
		// printf("\nb_parssing %d\n",error.b_parssing);//
		// printf("b_pipe %d\n",error.b_pipe);//
		// printf("b_fail_malloc %d\n",error.b_fail_malloc);//
		free(cmd_line);
		ft_free(token);
		// system("leaks minishell");
	}
	return (0);
}



		// token = ft_parse(cmd_line ,&error);
