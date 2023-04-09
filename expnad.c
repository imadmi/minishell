/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expnad.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 12:25:35 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/09 16:16:37 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

int	find_env_check(t_env *env, char *key)
{
	if (ft_strcmp(key, "?") == 0)
		return (1);
	while (env != NULL)
	{
		if (ft_strcmp(env->key, key) == 0)
		{
			return (1);
		}
		env = env->next;
	}
	return (0);
}

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

void	expand_value_suite(t_env *env, t_token *token)
{
	char	*key;
	char	*suff;

	key = token->value;
	if (!key)
		return ;
	if (ft_strcmp(key, "?") == 0)
	{
		free(key);
		token->value = ft_itoa(g_exit_status);
		return ;
	}
	suff = find_env(env, key);
	free(key);
	token->value = ft_strdup(suff);
	return ;
}
