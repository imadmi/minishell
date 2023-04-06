/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 12:31:57 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/06 12:33:09 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

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

void	ft_freeei(char **str, char **s, char **ss)
{
	int i;
	i = 0;
	free(*s);

	free(*ss);
	if (!str)
		return;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int ft_check(t_env *env, char	**s, char	*str)
{
	if (find_env(env, s[0]) != NULL && s[1] \
		&& (str[0] != '\'' && str[0] != '"'))
		return 1;
	return 0;
}

void ft_str2_protection(t_env *env, char **str2, char **s)
{
	*str2 = NULL;
    if (find_env(env, s[0]) != NULL && s[1] != NULL)
    {
        *str2 = malloc(ft_strlen(find_env(env, s[0])) + ft_strlen(s[1]) + 1);
        if (*str2 != NULL)
        {
            *str2[0] = '\0';
            ft_strlcat(*str2, find_env(env, s[0]), ft_strlen(find_env(env, s[0])) + 1);
            ft_strlcat(*str2, s[1], ft_strlen(*str2) + ft_strlen(s[1]) + 1);
        }
    }
}