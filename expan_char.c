/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expan_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 09:26:39 by imimouni          #+#    #+#             */
/*   Updated: 2023/04/12 11:01:53 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	ft_add_back_doll(t_token **token, char *value, t_exe *parssing)
{
	t_token	*last;
	t_token	*new;
	int		space_befor;

	ft_add_back_suite_dol(&new, value, parssing, &space_befor);
    free(value);
	if (new == NULL)
		return ;
	last = *token;
	if (last == NULL)
	{
		*token = new;
		return ;
	}
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new;
	new->prev = last;
}

t_token	*ft_token_expp(t_token *token, char *cmd_line, t_exe *err)
{
	int	pos;
	int	i;

	i = 0;
	pos = 0;
	while (cmd_line[i])
	{
		if (!ft_isspacee(cmd_line[i]) && !ft_sepaa(cmd_line[i]))
		{
			ft_token33(&i, cmd_line);
			ft_add_back_doll(&token, ft_substr(cmd_line, pos, i - pos), err);
			pos = i;
		}
		ft_token44(&i, cmd_line);
		if (ft_sepaa(cmd_line[i]))
		{
			ft_token55(&i, cmd_line);
			ft_add_back_doll(&token, ft_substr(cmd_line, pos, i - pos), err);
			pos = i;
		}
	}
	return (token);
}

int	tmp_dollar_signn(t_token *token)
{
	if (token->value != '\0' && token->prev)
	{
		while (token->prev)
		{
			if (!token->prev)
				break ;
			if (token->prev)
			{
				if ((ft_strcmp(token->prev->value, "'") == 0 || \
					contains_only_spaces(token->prev->value)))
					token = token->prev;
				else
					break ;
			}
		}
		if (token->prev && token->prev->prev)
			if (ft_strcmp(token->prev->prev->value, "@") == 0)
				return (0);
		if (token->prev)
			if (ft_strcmp(token->prev->value, "$") == 0)
				return (ft_checker(token));
	}
	return (0);
}

char	*join_tokenss(t_token *head)
{
	int			total_length;
	char		*result;
	t_token		*current;

	current = head;
	total_length = 0;
	while (current != NULL)
	{
		total_length += ft_strlen(current->value);
		current = current->next;
	}
	result = (char *)malloc((total_length + 1));
	if (result == NULL)
		return (NULL);
	result[0] = '\0';
	current = head;
	while (current != NULL)
	{
		ft_strcat(result, current->value);
		current = current->next;
	}
	return (result);
}

char	*exp_str(t_env *env, char *str)
{
    char *dup;
	t_token	*tmp;
	t_token	*tmp1;
	t_token	*head;
	if (!str)
		return (NULL);
	tmp = ft_token_expp(NULL, str, NULL);
	head = tmp;
	dup = NULL;
	if (contains_dollar(str))
	{
		while (tmp)
		{
			tmp1 = tmp;
			if (tmp_dollar_signn(tmp1))
				expanding_value(env, tmp);
			tmp = tmp->next;
		}
		dup = join_tokenss(head);
	}
	ft_free(head);
	return (dup);
}
