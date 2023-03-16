/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imimouni <imimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 10:29:30 by imimouni          #+#    #+#             */
/*   Updated: 2022/11/14 11:04:17 by imimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*the_copy;
	int		len;

	len = ft_strlen(s1) + 1;
	the_copy = (char *) malloc(sizeof(char) * len);
	if (the_copy)
		the_copy = ft_memcpy(the_copy, s1, len);
	return (the_copy);
}
