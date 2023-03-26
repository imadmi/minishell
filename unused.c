
// int contains_dollar(char *str)
// {
// 	int i = 0;
// 	while(str[i])
// 	{
// 		if (str[i] == '$')
// 			return 1;
// 		i++;
// 	}
//     return 0;
// }

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

// 	s_quote = 0;
// 	d_quote = 0;
// 	i = 0;
//     while (token->value[i])
// 	{
//         count_quotes(token->value[i], &s_quote, &d_quote);
//         if ((s_quote == 0) && !(d_quote % 2) )
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
