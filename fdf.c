/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 22:29:07 by rfontain          #+#    #+#             */
/*   Updated: 2018/06/03 19:04:29 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <mlx.h>
#include "libft/libft.h"

# define LEN_SEG 50
# define WIDTH 960
# define HEIGHT 720

typedef struct	s_pos
{
	int x;
	int y;
	int value;
}				t_pos;

typedef struct	s_grid
{
	t_pos **tab;
	int height;
	int width;
}				t_grid;

typedef struct	s_data
{
	void	*mlx;
	void	*win;
	t_grid	grid;
}				t_data;


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

void		ft_diffint(int *x, int *y, t_grid grid)
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

void	ft_initimage(t_grid grid)
{
	int i;
	int j;
	int diffx;
	int diffy;

	diffx = 0;
	diffy = 0;
	ft_diffint(&diffx, &diffy, grid);
	diffx = WIDTH / 2 - diffx;
	diffy = HEIGHT / 2 - diffy;
	i = 0;
	while (i < grid.height)
	{
		j = 0;
		while (j < grid.width)
		{
			grid.tab[i][j].x += diffx;
			grid.tab[i][j++].y += diffy;
		}
		i++;
	}
}

void	ft_putgrid(t_grid grid, void *param)
{
	int i;
	int j;
	t_pos **tab;

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

int		ft_widthtab(char *tab)
{
	int i;
	int res;

	res = 0;
	i = 0;
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

t_pos	**ft_iitotpos(int height, int width, int **tab)
{
	int i;
	int j;
	int xec;
	int yec;
	t_pos **ret;

	i = 0;
	yec = 0;
	ret = (t_pos**)malloc(sizeof(t_pos*) * height);
	while (i < height)
	{
		j = 0;
		xec = 0;
		ret[i] = (t_pos*)malloc(sizeof(t_pos) * width);
		while (j < width)
		{
			ret[i][j].x = xec;
			xec += LEN_SEG;
			ret[i][j].y = yec;
			ret[i][j].value = tab[i][j];
			j++;
		}
		yec += LEN_SEG;
		i++;
	}
	return (ret);
}

t_grid	ft_stoii(char **lines)
{
	t_grid	grid;
	int		**tab;
	char	tmp[32];
	t_pos	i;
	int		k;
	int		l;

	grid.height = 0;
	i.x = 0;
	while (lines[grid.height])
		grid.height++;
	tab = (int**)malloc(sizeof(int*) * grid.height);
	grid.width = ft_widthtab(lines[0]);
	while (i.x < grid.height)
	{
		i.y = 0;
		tab[i.x] = (int*)malloc(sizeof(int) * grid.width);
		l = 0;
		while (l < grid.width)
		{
			if (ft_isdigit(lines[i.x][i.y]))
			{
				k = 0;
				while (ft_isdigit(lines[i.x][i.y]))
					tmp[k++] = lines[i.x][i.y++];
				tmp[k] = '\0';
				tab[i.x][l++] = ft_atoi(tmp);
			}
			else
				i.y++;
		}
		i.x++;
	}
	grid.tab = ft_iitotpos(grid.height, grid.width, tab);
	return (grid);
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

int		deal_key(int key, void *param)
{
	t_data *data;

	data = param;
	printf("key : %d\n", key);
	if (key == 53 || key == 65307)
	{
		mlx_destroy_window((*data).mlx, (*data).win);
		exit(0);
	}
	if (key == 65362 || key == 65361 || key == 65363 || key == 65364 || key == 105)
	{
		mlx_clear_window((*data).mlx, (*data).win);
		if (key == 65362)
			ft_movegrid((*data).grid, 0, -LEN_SEG);
		else if (key == 65361)
			ft_movegrid((*data).grid, -LEN_SEG, 0);
		else if (key == 65364)
			ft_movegrid((*data).grid, 0, LEN_SEG);
		else if (key == 65363)
			ft_movegrid((*data).grid, LEN_SEG, 0);
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
		i = 0;
		while (i < data.grid.height)
		{
			j = 0;
			while (j < data.grid.width)
			{
				printf("tab[%d][%d] : %d:%d\n", i, j, data.grid.tab[i][j].x, data.grid.tab[i][j].y);
				j++;
			}
			i++;
		}
	}
	data.mlx = mlx_init();
	data.win = mlx_new_window(data.mlx, WIDTH, HEIGHT, "42");
	ft_putgrid(data.grid, &data);
	mlx_key_hook(data.win, deal_key, &data);
	mlx_loop(data.mlx);
}
