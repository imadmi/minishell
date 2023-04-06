/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 12:25:35 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/06 12:27:18 by imimouni         ###   ########.fr       */
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

char	*ft_strchr2(char *s, int c)
{
	char	*res;

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

char	*ft_strchr3(char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
		{
			return ft_strtrim(s, "$");
		}
		s++;
	}
	return (NULL);
}

void	expand_value_suite(t_env *env, t_token *token, int *i)
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
	free(token->value);
	token->value = ft_strdup(suff);
	free(suff);
	free(key);
}

void	expand_value_suite3(char *env_value, t_token *token, int *i)
{
	char	*key;
	char	*rest;
	char	*suff;

	key = ft_strtrim(ft_strchr(token->value, '$'), "$'\"");
	if (key == NULL)
		return;

	suff = malloc(ft_strlen(token->value) - (*i) + ft_strlen(env_value) + 1);
	ft_strlcpy(suff, token->value, (*i) + 1);
	ft_strlcat(suff, env_value, ft_strlen(token->value) + (*i) + ft_strlen(env_value) + 1);
	free(token->value);
	token->value = suff;
	free(key);
}