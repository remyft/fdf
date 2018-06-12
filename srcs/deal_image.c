/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 16:42:26 by rfontain          #+#    #+#             */
/*   Updated: 2018/06/12 18:34:18 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

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

void	ft_cartoiso(t_grid grid)
{
	int i;
	int j;
	int tile_half;
	int lim;

	i = 0;
	tile_half = (grid.tab[0][1].x - grid.tab[0][0].x) / 2;
	printf("tile : %d\n", tile_half);
	lim = 0;
	while (i < grid.height)
	{
		j = 0;
		while (j < grid.width)
		{
			if (((j - i) * tile_half) + 100 < lim)
				lim = ((j - i) * tile_half);
			printf("j - i : %d\nlime : %d\n", ((j - i) * tile_half) + 100, lim);
			grid.tab[i][j].x = ((j - i) * tile_half) + 100;
			grid.tab[i][j].y = ((j + i) * tile_half) + 100;

			/*grid.tab[i][j].x = (grid.tab[i][j].x - grid.tab[i][j].y) * tile_half;
			  grid.tab[i][j].y = (grid.tab[i][j].x + grid.tab[i][j].y) * tile_half;*/
			j++;
		}
		i++;
	}
	i = 0;
	while (i < grid.height)
	{
		j = 0;
		while (j < grid.width)
		{
			printf("tab[%d][%d] : %d:%d\n", i, j, grid.tab[i][j].x, grid.tab[i][j].y);
			j++;
		}
		i++;
	}
	ft_movegrid(grid, -lim + 10, 0);
	i = 0;
	while (i < grid.height)
	{
		j = 0;
		while (j < grid.width)
		{
			printf("tab[%d][%d] : %d:%d\n", i, j, grid.tab[i][j].x, grid.tab[i][j].y);
			j++;
		}
		i++;
	}
	grid.mod = 'i';
}

void	ft_isotocart(t_grid grid)
{
	int i;
	int j;
	int tile_half;

	tile_half = (grid.tab[0][1].x - grid.tab[0][0].x) / 2;
	i = 0;
	while (i < grid.height)
	{
		j = 0;
		while (j < grid.width)
		{
			grid.tab[i][j].x = ((grid.tab[i][j].x / tile_half) + (grid.tab[i][j].y / tile_half)) / 2;
			printf("grid - grid :%d\n", ((grid.tab[i][j].y / tile_half) - (grid.tab[i][j].x / tile_half)) / 2);
			grid.tab[i][j].y = ((grid.tab[i][j].y / tile_half) - (grid.tab[i][j].x / tile_half)) / 2;
			j++;
		}
		i++;
	}
	grid.mod = 'c';
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
			printf("i : %d\nj : %d\n", i, j);
			printf("width : %d\nheight : %d\n", grid.width, grid.height);
			if (i > 0)
			{
				printf("Ah\n");
				printf("%d\n%d\n%d\n%d\n", tab[i][j].x, tab[i][j].y, tab[i - 1][j].x, tab[i - 1][j].y);
				ft_printseg(tab[i][j].x, tab[i][j].y, tab[i - 1][j].x, tab[i - 1][j].y, param);
			}
			if (i < grid.height - 1)
			{
				printf("BEH\n");
				ft_printseg(tab[i][j].x, tab[i][j].y, tab[i + 1][j].x, tab[i + 1][j].y, param);
			}
			if (j > 0)
			{
				printf("CEH\n");
				ft_printseg(tab[i][j].x, tab[i][j].y, tab[i][j - 1].x, tab[i][j - 1].y, param);
			}
			if (j < grid.width - 1)
			{
				printf("DEH\n");
				ft_printseg(tab[i][j].x, tab[i][j].y, tab[i][j + 1].x, tab[i][j + 1].y, param);
			}
			j++;
		}
		i++;
	}
}
