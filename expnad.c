/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expnad.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 06:28:07 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/05 08:27:16 by imimouni         ###   ########.fr       */
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
	int		i;

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

void	ft_fre(char	**key, char	**suff, char **env_value)
{
	if ((*key))
		free((*key));
	if ((*env_value))
		free((*env_value));
	if ((*suff))
		free((*suff));
}

void	expand_value_suite3(t_env *env, t_token *token, int *i, int *flag)
{
	char	*key;
	char	*rest;
	char	*suff;

	key = ft_strtrim(ft_strchr(token->value, '$'), "$'\"");
	if (key == NULL)
		return;
	char *env_value = find_env(env, key);
	if (env_value == NULL)
		ft_fre(&key, &suff, &env_value);
	suff = malloc(ft_strlen(token->value) - (*i) + ft_strlen(env_value) + 1);
	if (!suff)
		ft_fre(&key, &suff, &env_value);
	ft_strlcpy(suff, token->value, (*i) + 1);
	ft_strlcat(suff, env_value, ft_strlen(token->value) + (*i) + ft_strlen(env_value) + 1);
	free(token->value);
	token->value = suff;
	free(key);
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
	char	*str;

	i = -1;
	str = ft_strchr2(token->value, '$');
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
					expand_value_suite(env, token, &i);
				else if (find_env(env, str) == NULL)
					expand_value_suite2(token, &i);
			}
		}
	}
	free(str);
}

int	count_wordss(char const *s, char c, char c1)
{
	int		i;
	int		words;

	words = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c &&  s[i] != c1 && (s[i + 1] == c  || s[i + 1] == c1 || s[i + 1] == '\0'))
			words++;
		i++;
	}
	return (words);
}

int	words_lenghtt(char const *s, char c, char c1)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (s[i] != c &&  s[i] != c1 && s[i] != '\0')
	{
		i++;
		len++;
	}
	return (len);
}

char	**ft_freee(int i, char **str)
{
	i--;
	while (--i >= 0)
		free(str[i--]);
	free (str);
	return (NULL);
}

char	**ft_filll(char const *s, int countwords, char c, char c1, char **spl_words)
{
	int		i;
	int		j;
	int		lenght;

	i = 0;
	while (i < countwords)
	{
		while (*s == c || *s == c1)
			s++;
		lenght = words_lenghtt(s, c, c1);
		spl_words[i] = (char *)malloc(sizeof(char) * (lenght + 1));
		if (spl_words == NULL)
			return (ft_freee(i, spl_words));
		j = 0;
		while (j < lenght)
			spl_words[i][j++] = *s++;
		spl_words[i][j] = '\0';
		i++;
	}
	spl_words[i] = NULL;
	return (spl_words);
}

char	**ft_splitt(char	const *s, char c, char c1)
{
	char	**spl_words;
	int		countwords;

	if (!s)
		return (NULL);
	countwords = count_wordss(s, c, c1);
	spl_words = (char **)malloc(sizeof(char *) * (countwords + 1));
	if (!spl_words)
		return (NULL);
	spl_words = ft_filll(s, countwords, c, c1, spl_words);
	return (spl_words);
}

void	expand_value2(t_env *env, t_token *token)
{
	int		i;
	char	*str;

	i = -1;
	str = ft_strchr3(token->value, '$');
	// printf("%s\n",str);
	// printf("%d\n",ft_strcmp(str,""));

	if (ft_strcmp(str,"") && char_quotes_type(str) == N_QUOTE)
	{
		if (token->prev != NULL)
			if (token->prev->type == RED_IN_D)
				return ;
		while (token->value[++i])
		{
			if (token->value[i] == '$')
			{
				if (find_env(env, str) != NULL)
					expand_value_suite(env, token, &i);
				if (find_env(env, str) == NULL)
					expand_value_suite2(token, &i);
			}
		}
	}
	free(str);
}

// void	expand_value2(t_env *env, t_token *token)
// {
// 	int i = 0;
// 	char **sp;
	
// 	// sp = ft_splitt(token->value, '\'', '"');
// 	sp = ft_split(token->value, '\'');
// 	while(sp[i])
// 	{
// 		printf("%s\n",sp[i]);
// 		i++;
// 	}
// }