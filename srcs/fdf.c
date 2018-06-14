/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 23:13:24 by rfontain          #+#    #+#             */
/*   Updated: 2018/06/07 19:19:53 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include <stdio.h>

int		deal_key(int key, void *param)
{
	t_data *data;

	data = param;
	printf("key : %d\n", key);
	/*if (key == 53)*/if (key == 65307)
	{
		mlx_destroy_window((*data).mlx, (*data).win);
		exit(0);
	}
	if (key == 65362 || key == 65361 || key == 65363 || key == 65364 || key == 61 || key == 45 || key == 105)
	//if (key == 34 || key == 126 || key == 123 || key == 125 || key == 124 || key == 69 || key == 78 || key == 0 || key == 2)
	{
		mlx_clear_window((*data).mlx, (*data).win);
		/*if (key == 126)*/if (key == 65362)
			ft_movegrid((*data).grid, 0, -LEN_SEG);
		else /*if (key == 123)*/if (key == 65361)
			ft_movegrid((*data).grid, -LEN_SEG, 0);
		else /*if (key == 125)*/if (key == 65364)
			ft_movegrid((*data).grid, 0, LEN_SEG);
		else /*if (key == 124)*/if (key == 65363)
			ft_movegrid((*data).grid, LEN_SEG, 0);
		else /*if (key == 78)*/if (key == 61)
		{
			ft_xtrans((*data).grid, (*data).grid.height, (*data).grid.width, 1);
			ft_ytrans((*data).grid, (*data).grid.height, (*data).grid.width, 1);
		}
		else /*if (key == 69)*/if (key == 45)
		{
			ft_xtrans((*data).grid, (*data).grid.height, (*data).grid.width, -1);
			ft_ytrans((*data).grid, (*data).grid.height, (*data).grid.width, -1);
		}
		else if (key == 0)
		{
			ft_xtrans((*data).grid, (*data).grid.height, (*data).grid.width, 1);
			ft_xrot((*data).grid, (*data).grid.height, (*data).grid.width, 1);
		}
		else if (key == 2)
		{
			ft_xtrans((*data).grid, (*data).grid.height, (*data).grid.width, -1);
			ft_xrot((*data).grid, (*data).grid.height, (*data).grid.width, -1);
		}
		else
			ft_initimage((*data).grid);
		ft_putgrid((*data).grid, data);
	}

	return (0);
}


int main(int ac, char **av)
{
	t_data data;
	int fd;
	int i;
	int j;
	char **lines;

	i = 0;
	lines = malloc(sizeof(char*) * 100);
	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		while (get_next_line(fd, &lines[i]) == 1)
			i++;
		lines[i] = NULL;
		data.grid = ft_stoii(lines);
		ft_initimage(data.grid);
		/*i = 0;
		while (i < data.grid.height)
		{
			j = 0;
			while (j < data.grid.width)
			{
				printf("tab[%d][%d] : %d:%d\n", i, j, data.grid.tab[i][j].x, data.grid.tab[i][j].y);
				j++;
			}
			i++;
		}*/
	}
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "42");
	i = 0;
	while (i < data.grid.height)
	{
		j = 0;
		while (j < data.grid.width)
		{
			ft_putchar('[');
			ft_putnbr(data.grid.tab[i][j].x);
			ft_putchar(',');
			ft_putnbr(data.grid.tab[i][j].y);
			ft_putchar(']');
			j++;
		}
		ft_putchar('\n');
		i++;
	}
	ft_cartoiso(data.grid, data.grid.height, data.grid.width);
	ft_putgrid(data.grid, &data);
	i = 0;
	while (i < data.grid.height)
	{
		j = 0;
		while (j < data.grid.width)
		{
			ft_putstr("[");
			ft_putnbr(i);
			ft_putchar(':');
			ft_putnbr(data.grid.tab[i][j].x);
			ft_putstr(",");
			ft_putnbr(j);
			ft_putchar(':');
			ft_putnbr(data.grid.tab[i][j].y);
			ft_putchar(']');
			j++;
		}
		ft_putchar('\n');
		i++;
	}
	ft_printseg(325, 325, 375, 350, &data);
	mlx_key_hook(data.win, deal_key, &data);
	mlx_loop(data.mlx);
}
