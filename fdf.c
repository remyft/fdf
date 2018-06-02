/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 22:29:07 by rfontain          #+#    #+#             */
/*   Updated: 2018/05/31 17:29:15 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <mlx.h>
#include "libft/libft.h"

# define LEN_SEG 120
# define WIDTH 960
# define HEIGHT 735

typedef struct	s_data
{
	void	*mlx;
	void	*win;
}				t_data;

typedef struct	s_file
{
	int width;
	int heigth;
	char *tab;
}				t_file;

typedef struct	s_grid
{
	int **tab;
	int height;
	int width;
}				t_grid;

int		deal_key(int key, void *param)
{
	t_data *data;

	data = param;
	if (key == 53 || key == 65307)
	{
		mlx_destroy_window((*data).mlx, (*data).win);
		exit(1);
	}
	return (0);
}

void	ft_printseg(int x1, int y1, int x2, int y2, void *param, int col)
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
		mlx_pixel_put((*data).mlx, (*data).win, x, y, 16777215 - (1000 * col));
		if ((e = e + e10) >= 0.5)
		{
			y = y + 1;
			e = e + e01;
		}
		x == x2 ? x2 : x++;
	}
}

void	ft_putgrid(t_grid grid, void *param)
{
	int i;
	int j;
	int x;
	int y;

	y = 50;
	i = 0;
	while (i < grid.height)
	{
		x = 50;
		j = 0;
		while (j < grid.width)
		{
		//	if (i > 0)
		//		ft_printseg(x, y, x, y - LEN_SEG, param, grid.tab[i][j]);
			if (i < grid.height - 1)
				ft_printseg(x, y, x, y + LEN_SEG, param, grid.tab[i + 1][j]);
		//	if (j > 0)
		//		ft_printseg(x, y, x - LEN_SEG, y, param, grid.tab[i][j]);
			if (j < grid.width - 1)
				ft_printseg(x, y, x + LEN_SEG, y, param, grid.tab[i][j + 1]);
			x += LEN_SEG;
			j++;
		}
		y += LEN_SEG;
		i++;
	}
}

int		ft_widthtab(char *tab)
{
	int i;
	int res;

	while (tab[i])
	{
		if (ft_isdigit(tab[i]))
		{
			res++;
			while (ft_isdigit(tab[i]))
				i++;
		}
		else
			i++;
	}
	return (res);
}

t_grid	ft_stoii(char **lines)
{
	t_grid	grid;
	char	tmp[32];
	int		i;
	int		j;
	int		k;
	int		l;

	grid.height = 0;
	i = 0;
	while (lines[grid.height])
		grid.height++;
	grid.height--;
	grid.tab = malloc(sizeof(int*) * grid.height);
	grid.width = ft_widthtab(lines[0]);
	while (lines[i])
	{
		j = 0;
		grid.tab[i] = malloc(sizeof(int) * grid.width);
		l = 0;
		while (lines[i][j])
		{
			if (ft_isdigit(lines[i][j]))
			{
				k = 0;
				while (ft_isdigit(lines[i][j]))
					tmp[k++] = lines[i][j++];
				tmp[k] = '\0';
				grid.tab[i][l++] = ft_atoi(tmp);
			}
			else
				j++;
		}
		i++;
	}
	return (grid);
}

int main (int ac, char **av)
{
	t_data data;
	t_grid grid;
	int fd;
	int i;
	int j;
	char **lines;

	i = 0;
	lines = malloc(sizeof(char*) * 100);
	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		ft_putchar('H');
		while (get_next_line(fd, &lines[i]) == 1)
		{
			ft_putchar(i++ + 48);
			}
		ft_putchar('A');
		lines[i] = "\0";
		grid = (ft_stoii(lines));
		ft_putchar('I');
		/*i = 0;
		while (i < grid.height)
		{
			j = 0;
			while (j < grid.width)
				ft_putnbr(grid.tab[i][j++]);
			ft_putchar('\n');
			i++;
		}*/
	}
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "42");
	ft_putgrid(grid, &data);
	mlx_key_hook(data.win, deal_key, &data);
	mlx_loop(data.mlx);
}
