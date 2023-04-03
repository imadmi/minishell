/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expnad.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 06:28:07 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/03 08:21:27 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

char	*find_env(t_env *env, char *key)
{
	while (env != NULL)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			return (env->value);
		}
		env = env->next;
	}
	return (NULL);
}

char	*ft_strchr2(char *s, int c, int *flag)
{
	int		i;
	int		quotes[2];
	char	*res;

	quotes[0] = 0;
	quotes[1] = 0;
	i = ft_strlen(s);
	while (i > 0 && !ft_isalnum(s[i - 1]))
		count_quotes(s[--i], &quotes[0], &quotes[1]);
	if (quotes[0] == 1)
		(*flag) = 1;
	while (*s)
	{
		if (*s == (char)c)
		{
			res = ft_strtrim(s, "$");
			return (res);
		}
		s++;
	}
	return (NULL);
}

void	expand_value_suite(t_env *env, t_token *token, int *i, int *flag)
{
	char	*key;
	char	*suff;

	key = ft_strtrim(ft_strchr(token->value, '$'), "$");
	if (!key)
		return ;
	suff = malloc(ft_strlen(find_env(env, key)) + (*i) + 2);
	if (!suff)
	{
		free(key);
		return ;
	}
	ft_strlcpy(suff, token->value, (*i) + 1);
	ft_strlcat(suff, find_env(env, key), \
	ft_strlen(find_env(env, key)) + (*i) + 2);
	if (*flag)
		ft_strlcat(suff, "'", ft_strlen(find_env(env, key)) + (*i) + 2);
	free(token->value);
	token->value = ft_strdup(suff);
	free(suff);
	free(key);
	(*i) = -1;
}

void	expand_value_suite2(t_token *token, int *i)
{
	char	*suff;

	suff = malloc((*i) + 2);
	if (!suff)
		return ;
	ft_strlcpy(suff, token->value, (*i) + 1);
	free(token->value);
	token->value = ft_strdup(suff);
	free(suff);
	(*i) = -1;
}

void	expand_value(t_env *env, t_token *token)
{
	int		i;
	int		flag;
	char	*str;

	i = -1;
	flag = 0;
	str = ft_strchr2(token->value, '$', &flag);
	if (ft_strchr(token->value, '$') && token->quote != S_QUOTE)
	{
		if (token->prev != NULL)
			if (token->prev->type == RED_IN_D)
				return ;
		while (token->value[++i])
		{
			if (token->value[i] == '$')
			{
				if (find_env(env, str) != NULL)
					expand_value_suite(env, token, &i, &flag);
				else if (find_env(env, str) == NULL)
					expand_value_suite2(token, &i);
			}
		}
	}
	free(str);
}
