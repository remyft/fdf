/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 16:42:26 by rfontain          #+#    #+#             */
/*   Updated: 2018/06/05 20:59:29 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ft_xtrans(t_grid grid, int height, int width, int z)
{
	int	i;
	int	j;
	int	x;
	int	lim;

	(width % 2 != 0) ? (lim = width / 2) : (lim = width / 2 + 1);
	i = 0;
	x = 1 * z;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (j < lim)
				grid.tab[i][j].x += x * (lim - j);
			else if (j > lim)
				grid.tab[i][j].x -= x * (j - lim);
			j++;
		}
		i++;
	}
}

void	ft_ytrans(t_grid grid, int height, int width, int z)
{
	int i;
	int j;
	int x;
	int lim;

	(height % 2 != 0) ? (lim = height / 2) : (lim = height / 2 + 1);
	i = 0;
	x = 1 * z;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (i < lim)
				grid.tab[i][j].y += x * (lim - i);
			else if (i > lim)
				grid.tab[i][j].y -= x * (i - lim);
			j++;
		}
		i++;
	}
}

void	ft_xrot(t_grid grid, int height, int width, int z)
{
	int i;
	int j;
	int limj;
	int limi;
	int x;

	(width % 2 != 0) ? (limj = width / 2) : (limj = width / 2 + 1);
	(height % 2 != 0) ? (limi = height / 2) : (limi = height / 2 + 1);
	i = 0;
	x = 1;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (j < limj)
			{
				if (i < limi)
					grid.tab[i][j].y += ((x * z) * (limj - j)) * (limi - i);
				else
					grid.tab[i][j].y -= ((x * z) * (limj - j)) * (i - limi);
			}
			else if (j > limj)
			{
				if (i < limi)
					grid.tab[i][j].y -= ((x * z) * (j - limj)) * (limi - i);
				else
					grid.tab[i][j].y += ((x * z) * (j - limj)) * (i - limi);
			}
			j++;
		}
		i++;
	}
}

void	ft_movegrid(t_grid grid, int x, int y)
{
	int i;
	int j;

	i = 0;
	while (i < grid.height)
	{
		j = 0;
		while (j < grid.width)
		{
			grid.tab[i][j].x += x;
			grid.tab[i][j++].y += y;
		}
		i++;
	}
}

void	ft_initimage(t_grid grid)
{
	int diffx;
	int diffy;

	diffx = 0;
	diffy = 0;
	ft_diffint(&diffx, &diffy, grid);
	diffx = WIDTH / 2 - diffx;
	diffy = HEIGHT / 2 - diffy;
	ft_movegrid(grid, diffx, diffy);
}

void	ft_putgrid(t_grid grid, void *param)
{
	int		i;
	int		j;
	t_pos	**tab;

	i = 0;
	tab = grid.tab;
	while (i < grid.height)
	{
		j = 0;
		while (j < grid.width)
		{
			if (i < grid.height - 1)
				ft_printseg(tab[i][j].x, tab[i][j].y, tab[i][j].x, tab[i + 1][j].y, param);
			if (j < grid.width - 1)
				ft_printseg(tab[i][j].x, tab[i][j].y, tab[i][j + 1].x, tab[i][j].y, param);
			j++;
		}
		i++;
	}
}
