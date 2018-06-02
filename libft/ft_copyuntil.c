/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_copyuntil.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/17 22:22:38 by rfontain          #+#    #+#             */
/*   Updated: 2018/05/26 19:04:13 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_copyuntil(char **dst, char *src, char c)
{
	int		i;
	int		count;
	char	*tmp;

	i = 0;
	count = 0;
	while (src[i])
	{
		if (src[i] == c)
			break ;
		i++;
	}
	tmp = *dst;
	if (!(*dst = ft_strnew(i)))
		return (0);
	free(tmp);
	while (src[count] && count < i)
	{
		tmp = *dst;
		if (!(*dst = ft_strjoinch(*dst, src[count])))
			return (0);
		free(tmp);
		count++;
	}
	return (i);
}
