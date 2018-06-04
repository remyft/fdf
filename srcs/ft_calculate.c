/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calculate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 23:06:36 by rfontain          #+#    #+#             */
/*   Updated: 2018/06/04 23:23:41 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ft_printseg(int x1, int y1, int x2, int y2, void *param)
{
	int x;
	int y;
	int dx;
	int dy;
	float e;
	float e01;
	float e10;
	t_data *data;

	data = param;
	dx = x2 - x1;
	dy = y2 - y1;
	y = y1;
	e = 0.0;
	if (dx == 0)
		dx++;
	e10 = (float) dy / dx;
	e01 = -1.0;
	x = x1;
	while (x < x2 || y < y2)
	{
		mlx_pixel_put((*data).mlx, (*data).win, x, y, 16777215);
		if ((e = e + e10) >= 0.5)
		{
			y = y + 1;
			e = e + e01;
		}
		x == x2 ? x2 : x++;
	}
}

void	ft_diffint(int *x, int *y, t_grid grid)
{
	int i;
	int j;
	int k;
	int l;

	if (grid.width % 2 == 0)
	{
		k = grid.width / 2 - 1;
		i = grid.tab[0][k].x;
		j = grid.tab[0][k + 1].x;
		i = (i + j) / 2;
	}
	else
		i = grid.tab[0][grid.width / 2].x;
	if (grid.height % 2 == 0)
	{
		l = grid.height / 2 - 1;
		j = grid.tab[l][0].y;
		k = grid.tab[l + 1][0].y;
		j = (k + j) / 2;
	}
	else
		j = grid.tab[grid.height / 2][0].y;
	*x = i;
	*y = j;
}
