/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 22:29:07 by rfontain          #+#    #+#             */
/*   Updated: 2018/05/30 19:58:14 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <mlx.h>
#include "GNL/get_next_line.h"

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

int		deal_key(int key, void *param)
{
	t_data *data;

	data = param;
	if (key == 53)
		mlx_destroy_window((*data).mlx, (*data).win);
	return (0);
}

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
	printf("e10 : %f\n", e10);
	e01 = -1.0;
	x = x1;
	while (x < x2 || y < y2)
	{
		mlx_pixel_put((*data).mlx, (*data).win, x, y, 0XFFFFFF);
		if ((e = e + e10) >= 0.5)
		{
			y = y + 1;
			e = e + e01;
		}
		x == x2 ? x2 : x++;
	}
}

void	ft_putgrid(char **lines, void *param)
{
	int i;
	int j;
	int x;
	int y;

	x = 50;
	i = 0;
	while (lines[i])
	{
		y = 50;
		j = 0;
		while (lines[i][j] && lines[i][j] == '0')
		{
			if (i > 0 && lines[i - 1][j])
				ft_printseg(x, y, x, y - 10, param);
			if (lines[i + 1][j])
				ft_printseg(x, y, x, y + 10, param);
			if (lines[i][j - 2] && lines[i][j - 2] == '0')
				ft_printseg(x, y, x - 10, y, param);
			if (lines[i][j + 2] && lines[i][j - 2] == '0')
				ft_printseg(x, y, x + 10, y, param);
			y += 10;
			j++;
		}
		x += 10;
		i++;
	}
}

int main (int ac, char **av)
{
	t_data data;
	int x;
	int y;
	int fd;
	int i;
	char *lines[100];

	i = 0;
	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		while (get_next_line(fd, &lines[i]))
			i++;
		lines[i] = "\0";
		i = 0;
		while (lines[i])
		{
			ft_putstr(lines[i++]);
			ft_putchar('\n');
		}
	}
	y = 105;
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, 420, 420, "42");
	/*while (y < 315)
	{
		x = 105;
		while (x < 315)
		{
			mlx_pixel_put(data.mlx, data.win, x, y, 0XFFFFFF);
			x++;
		}
		y++;
	}
	ft_printseg(105, 210, 315, 210, &data);*/
	ft_putgrid(&lines[0], &data);
	mlx_key_hook(data.win, deal_key, &data);
	mlx_loop(data.mlx);
}
