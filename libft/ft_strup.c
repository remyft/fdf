/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strup.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/19 06:45:50 by rfontain          #+#    #+#             */
/*   Updated: 2018/09/19 06:45:52 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strup(char *str, size_t size)
{
	size_t i;

	i = 0;
	while (i < size)
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
}
