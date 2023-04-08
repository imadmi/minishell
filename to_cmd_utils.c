/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_cmd_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 14:21:17 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/08 16:42:47 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void print_cmds(t_cmd *cmds)
{
	if (cmds == NULL) {
		printf("No commands to print.\n");
		return;
	}
	
    t_cmd *current_cmd = cmds;
	int i;
	
    while (current_cmd != NULL)
	{
		i = 0;
        printf("Command:\n");
        printf("  Arguments:\n");
        while (current_cmd->args[i] != NULL)
		{
            printf("    %s\n", current_cmd->args[i]);
			i++;
        }
		
		printf("  Redirections:\n");
        t_red *current_red = current_cmd->red;
        while (current_red != NULL)
		{
            switch (current_red->type)
			{
                case RED_IN:
                    printf("    < %s\n", current_red->filename);
                    break;
                case RED_OUT:
                    printf("    > %s\n", current_red->filename);
                    break;
                case RED_IN_D:
                    printf("    << %s\n", current_red->filename);
                    break;
                case RED_OUT_D:
                    printf("    >> %s\n", current_red->filename);
                    break;
                default:
                    break;
            }
			print_token_name(current_red->type);
			print_token_name(current_red->quotes);
            current_red = current_red->next;
        }
		
        current_cmd = current_cmd->next;
    }
}

int nbr_words(t_token	*tmp)
{
	t_token	*token;

	token = tmp;
	int i = 0;
	while (token != NULL && token->type != PIPE)
	{
		if (token->type == WORD || token->type == DOLLAR)
			i++;
		token = token->next;
	}
	return (i + 1);
}

int nbr_herdoc(t_token	*tmp)
{
	t_token	*token;

	token = tmp;
	int i = 0;
	while (token != NULL && token->type != PIPE)
	{
		if (token->type == RED_IN_D)
			i++;
		token = token->next;
	}
	return (i);
}

// void	exp_token(t_env *env, t_token *token)
// {
// 	char	*str;
// 	char	**s;
	
// 	while (token != NULL)
// 	{
// 		if(token->quote == D_QUOTE && has_dollar_sign(token->value))
			// expand_value(env ,token);
// 		else if(token->quote == N_QUOTE && has_dollar_sign(token->value))
// 		{
// 			if (token->prev != NULL)
// 				if (token->prev->type == RED_IN_D)
// 				{
// 					token = token->next ;
// 					continue;
// 				}
// 				expand_value2(env, token,str,s);
// 		}
// 		if(has_dollar_sign(token->value))
			// remove_quotesv2(token);
// 		token = token->next;
// 	}
// }

char *ft_strncpy(char *dest, const char *src, size_t n)
{
    size_t i = 0;

    while (i < n && src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }

    while (i < n) {
        dest[i] = '\0';
        i++;
    }

    return dest;
}


char **split_string_at_dollar(char *string)
{
    char **result = (char**) malloc(2 * sizeof(char*));

    if (result == NULL)
		return NULL;

    char *dollar_ptr = ft_strchr(string, '$');

    if (dollar_ptr == NULL)
		return NULL;

    size_t dollar_index = dollar_ptr - string;

    result[0] = (char*) malloc((dollar_index + 1) * sizeof(char));

    if (result[0] == NULL)
		return NULL;

    ft_strncpy(result[0], string, dollar_index);
    result[0][dollar_index] = '\0';

    result[1] = dollar_ptr;
    return result;
}



int	ft_isspacee(int c)
{
	// if (c == '"')
	// 	return (1);
	return (0);
}

int	ft_sepaa(char c)
{
	// if (c == '"')
	if (c == '"' || c == '\'' || c == '$')
		return (1);
	return (0);
}

int	ft_token22(int *j, char cmd_line, int *single_quote, int *double_quote)
{
	count_quotes(cmd_line, single_quote, double_quote);
	if (((*single_quote) % 2) || ((*double_quote) % 2))
	{
		(*j)++;
		return (1);
	}
	return (0);
}

void	ft_token33(int *j, char *cmd_line, int *single_quote, int *double_quote)
{
	count_quotes(cmd_line[*j], single_quote, double_quote);
	while ((cmd_line[*j] && !ft_isspacee(cmd_line[*j])
			&& !ft_sepaa(cmd_line[*j])) || (cmd_line[*j]
			&& ((*single_quote) % 2 || (*double_quote) % 2)))
	{
		count_quotes(cmd_line[*j], single_quote, double_quote);
		if ((*double_quote) % 2 || (*single_quote) % 2)
			(*j)++;
		if ((*double_quote) % 2 || (*single_quote) % 2)
			continue ;
		(*j)++;
	}
}

void	ft_token44(int *j, char *cmd_line)
{
	while (cmd_line[(*j)] && ft_isspacee(cmd_line[(*j)]))
	{
		(*j)++;
		continue ;
	}
}

void	ft_token55(int *j, char *cmd_line)
{
	if (cmd_line[(*j)] && ft_sepaa(cmd_line[(*j)]))
	{
		(*j)++;
	}
}


t_token	*ft_token_exp(t_token *token, char *cmd_line, t_exe *err)
{
	int	quotes[2];
	int	pos;
	int	i;

	ft_token1(&pos, &i, &quotes[0], &quotes[1]);
	while (cmd_line[i])
	{
		// if (ft_token22(&i, cmd_line[i], &quotes[0], &quotes[1]))
		// 	continue ;
		if (!ft_isspacee(cmd_line[i]) && !ft_sepaa(cmd_line[i]))
		{
			ft_token33(&i, cmd_line, &quotes[0], &quotes[1]);
			ft_add_back(&token, ft_substr(cmd_line, pos, i - pos), err);
			pos = i;
		}
		ft_token44(&i, cmd_line);
		if (ft_sepaa(cmd_line[i]))
		{
			ft_token55(&i, cmd_line);
			ft_add_back(&token, ft_substr(cmd_line, pos, i - pos), err);
			pos = i;
		}
	}
	return (token);
}


// void expanding_value(t_env *env, t_token *token)
// {
//     int i;
//     char *str2;
//     char *str;
//     char **s;

//     str = ft_strchr3(token->value, '$');
//     s = ft_split(str,'"');
//     i = -1;
// 	ft_str2_protection(env, &str2, s);
//     if (ft_strcmp(str, "") && str != NULL && s[0] != NULL)
//     {
//         while (token->value[++i])
//         {
//             if (token->value[i] == '$')
//             {
//                 if (find_env(env, str) != NULL)
//                     expand_value_suite(env, token, &i);
//                 else if (ft_check(env, s, str))
//                     expand_value_suite3(str2, token, &i);
//                 else if (find_env(env, s[0]) == NULL && str2 != NULL)
//                     expand_value_suite3(str, token, &i);
//                 else if (find_env(env, str) == NULL && str2 == NULL)
//                     expand_value_suite2(token, &i);
//             }
//         }
//     }
//     ft_freeei(s, &str, &str2);
// }

void expanding_value(t_env *env, t_token *token)
{
    int i;
    // char *str2;
    // char **s;
    char *str;

    // str = ft_strchr3(token->value, '$');
    str = token->value;
    // s = ft_split(str,'"');
    // i = -1;
	// ft_str2_protection(env, &str2, s);
    // if (ft_strcmp(str, "") && str != NULL && s[0] != NULL)
    if (ft_strcmp(str, "") && str != NULL)
    {
    printf(">>%s\n",str);
        // while (token->value[++i])
        // {
            // if (token->value[i] == '$')
            // {
                if (find_env(env, str) != NULL)
                    expand_value_suite(env, token);
                // else if (ft_check(env, s, str))
                //     expand_value_suite3(str2, token, &i);
                // else if (find_env(env, s[0]) == NULL && str2 != NULL)
                //     expand_value_suite3(str, token, &i);
                // else if (find_env(env, str) == NULL && str2 == NULL)
                //     expand_value_suite2(token, &i);
            // }
        // }
    }
    // ft_freeei(s, &str, &str2);
}

void remove_quotess(char *str)
{
    int len = ft_strlen(str);
    int i = 0, j = 0;
    while (i < len) {
        if (str[i] != '"' && str[i] != '\'') {
            str[j] = str[i];
            j++;
        }
        i++;
    }
    str[j] = '\0';
}

char* ft_strcat(char* dest, const char* src)
{
    char* dest_end = dest;
    while (*dest_end != '\0') {
        ++dest_end;
    }
    while (*src != '\0')
    {
        *dest_end = *src;
        ++dest_end;
        ++src;
    }
    *dest_end = '\0';
    return dest;
}

char* join_tokens(t_token* head)
{
    size_t total_length = 0;
    t_token* current = head;
    while (current != NULL)
    {
        total_length += ft_strlen(current->value);
        current = current->next;
    }
    char* result = (char*)malloc((total_length + 1));
    if (result == NULL)
        return NULL;
    result[0] = '\0';
    current = head;
    while (current != NULL)
    {
        ft_strcat(result, current->value);
        current = current->next;
    }
    remove_quotess(result);
    return result;
}

int	ft_sigle_q(t_token *token)
{
    if (token->value != '\0' && token != NULL)
	{
        if (token->prev && token->next && \
        ft_strcmp(token->next->value,"'") == 0 && ft_strcmp(token->prev->value,"'") == 0)
			return 1;
    }
    return 0;
}

void	exp_token(t_env *env, t_token *token)
{
    t_token *tmp;
    t_token *tmp1;
    t_token *head;
	int		i;

	while (token != NULL)
	{
		// if (has_dollar_sign(token->value) && token->quote != S_QUOTE)
		// {
			i = -1;
            tmp = ft_token_exp(NULL, token->value , NULL);
            head = tmp;
            while(tmp)
            {
                tmp1 = tmp;
                if (tmp_dollar_sign(tmp1) && !ft_sigle_q(tmp1))
                {
                    expanding_value(env ,tmp);
                }
                tmp = tmp->next;
            }
            // print_token(head);
            free(token->value);
            token->value = join_tokens(head);
            ft_free(head);
		// }
		token = token->next;
	}
}
