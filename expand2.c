/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 12:25:35 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/07 20:34:28 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

static int	nbr_of_digits(int nbr)
{
	int		i;

	i = 0;
	if (nbr == 0)
		return (1);
	if (nbr < 0)
		i = 1;
	while (nbr != 0)
	{
		nbr /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	long	nbr;
	char	*result;
	int		len;
	int		size;

	size = 0;
	if (n < 0)
		size = 1;
	len = nbr_of_digits(n);
	result = (char *)malloc((len + 1));
	if (!result)
		return (result);
	nbr = n;
	if (nbr < 0)
		nbr *= -1;
	result[len] = '\0';
	while (--len >= size)
	{
		result[len] = (nbr % 10) + '0';
		nbr /= 10;
	}
	return (result);
}


char	*find_env(t_env *env, char *key)
{
	while (env != NULL)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			return (env->value);
		}
		if (ft_strcmp(env->key, key) == 0 || ft_strcmp(key, "$?"))
		{
			return (ft_itoa(exit_status));
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