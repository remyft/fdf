/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 16:42:47 by rfontain          #+#    #+#             */
/*   Updated: 2018/06/12 18:47:02 by rfontain         ###   ########.fr       */
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
	if ((dx = x2 - x1) < 0)
		dx = -dx;
	if ((dy = y2 - y1) < 0)
		dy = -dy;
	//dx = x2 - x1;// < 0 ?: -dx ;
	//dy = y2 - y1;// < 0 ?: -dy;
	printf("dx : %d\ndy : %d\n", dx, dy);
	y = y1;
	e = 0.0;
	if (dx == 0)
		dx++;
	e10 = (float) dy / dx;
	e01 = -1.0;
	x = x1;
	printf("y1 : %d\n", y1);
	while (x != x2 || y != y2)
	{
		mlx_pixel_put((*data).mlx, (*data).win, x, y, 16777215);
		if ((e = e + e10) >= 0.5)
		{
			if (y < y2)
				y++;
			else if (y > y2)
				y--;
			printf("y : %d\n", y);
			/*y = (y <= y2) ?: y++;
			y = (y >= y2) ?: y--;*/
			e = e + e01;
		}
		if (x < x2)
			x++;
		else if (x > x2)
			x--;
		/*x = x <= x2 ?: x++;
		x = x >= x2 ?: x--;*/
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
