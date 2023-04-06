/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 12:28:45 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/06 12:29:03 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "parsing.h"

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
