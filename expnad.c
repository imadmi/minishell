/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expnad.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 06:28:07 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/08 16:09:47 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

// void expand_value2(t_env *env, t_token *token, char *str, char **s)
// {
//     int i;
//     char *str2;

//     str = ft_strchr3(token->value, '$');
//     s = ft_splitt(str, '\'', '"');
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

// void	expand_value2(t_env *env, t_token *token,char	*str,char	**s)
// {
// 	int		i;
// 	char	*str2;

// 	str = ft_strchr3(token->value, '$');
// 	s = ft_splitt(str, '\'', '"');
// 	i = -1;
// 	str2 = ft_strjoin(find_env(env, s[0]),s[1]);
// 	// printf("%s",str2);
// 	// printf("%s\n",str);
// 	// printf("%d\n",ft_strcmp(str,""));
// 	if (ft_strcmp(str,"") && str && s[0])
// 	{
// 		while (token->value[++i])
// 		{
// 			if (token->value[i] == '$')
// 			{
// 				if (find_env(env, str) != NULL)
// 					expand_value_suite(env, token, &i);
// 				else if (ft_check(env, s, str))
// 					expand_value_suite3(str2, token, &i);
// 				else if (find_env(env, s[0]) == NULL && str2)
// 					expand_value_suite3(str, token, &i);
// 				else if (find_env(env, str) == NULL && !str2)
// 					expand_value_suite2(token, &i);
// 			}
// 		}
// 	}
// 	ft_freeei(s , &str, &str2);
// }

	//remove quotes