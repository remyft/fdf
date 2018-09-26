/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 22:52:23 by rfontain          #+#    #+#             */
/*   Updated: 2018/09/26 14:42:26 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	bresenhamx(t_pos pos, int dx, int dy, t_env env)
{
	int cumul;
	int incx;
	int incy;
	int i;

	incx = (dx > 0) ? 1 : -1;
	incy = (dy > 0) ? 1 : -1;
	cumul = dx / 2;
	dx = ft_abs(dx);
	dy = ft_abs(dy);
	i = 1;
	while (i <= dx)
	{
		pos.x += incx;
		cumul += dy;
		if (cumul >= dx)
		{
			cumul -= dx;
			pos.y += incy;
		}
		mlx_pixel_put(env.mlx, env.win, pos.x, pos.y, pos.value);
		i++;
	}
}

static void	bresenhamy(t_pos pos, int dx, int dy, t_env env)
{
	int cumul;
	int incx;
	int incy;
	int i;

	incx = (dx > 0) ? 1 : -1;
	incy = (dy > 0) ? 1 : -1;
	cumul = dy / 2;
	dx = ft_abs(dx);
	dy = ft_abs(dy);
	i = 1;
	while (i <= dy)
	{
		pos.y += incy;
		cumul += dx;
		if (cumul >= dy)
		{
			cumul -= dy;
			pos.x += incx;
		}
		mlx_pixel_put(env.mlx, env.win, pos.x, pos.y, pos.value);
		i++;
	}
}

void		print_seg(t_pos pos1, t_pos pos2, t_pos col, t_env env)
{
	t_pos	pos;
	int		dx;
	int		dy;

	dx = pos2.x - pos1.x;
	dy = pos2.y - pos1.y;
	if (col.x <= 0 || col.y <= 0)
		pos.value = 0x00FF00;
	else if (col.x <= 7 || col.y <= 7)
		pos.value = 0x736845;
	else
		pos.value = 0xFFFFFF;
	pos.x = pos1.x;
	pos.y = pos1.y;
	if (ft_abs(dx) > ft_abs(dy))
		bresenhamx(pos, dx, dy, env);
	else
		bresenhamy(pos, dx, dy, env);
}

void		change_height(void *param, int hg)
{
	t_env	*env;
	int		i;
	int		j;

	env = param;
	i = 0;
	while (i < (*env).height)
	{
		j = 0;
		while (j < (*env).width)
		{
			if ((*env).value[i][j] > 0)
				(*env).igrid[i][j] += (hg * (*env).value[i][j]) * (*env).lenseg / 50;
			j++;
		}
		i++;
	}
	(*env).pgrid = transform_to_pos((*env).height, (*env).width, (*env).igrid,
			(*env));
}
