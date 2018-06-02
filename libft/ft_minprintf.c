/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/14 05:11:31 by rfontain          #+#    #+#             */
/*   Updated: 2018/04/14 05:11:50 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_minprintf(char *str, int nb1, int nb2)
{
	int i;
	int nb;

	i = 0;
	nb = 1;
	while (str[i])
	{
		if (str[i] == '%')
		{
			(nb == 1 ? ft_putnbr(nb1) : ft_putnbr(nb2));
			nb++;
			i++;
		}
		else
			ft_putchar(str[i]);
		i++;
	}
}
