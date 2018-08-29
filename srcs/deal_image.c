/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 18:21:53 by rfontain          #+#    #+#             */
/*   Updated: 2018/08/28 05:44:27 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	cartoiso(void *param)
{
	int		tmpx;
	int		tmpy;
	int		i;
	int		j;
	t_env	*env;

	env = param;
	i = 0;
	while (i < (*env).height)
	{
		j = 0;
		while (j < (*env).width)
		{
			tmpx = (*env).pgrid[i][j].x;
			tmpy = (*env).pgrid[i][j].y;
			(*env).pgrid[i][j].x = (tmpx - tmpy);
			(*env).pgrid[i][j].y = (tmpx + tmpy) / 2;
			j++;
		}
		i++;
	}
}

void	isotocar(void *param)
{
	int		tmpx;
	int		tmpy;
	int		i;
	int		j;
	t_env	*env;

	env = param;
	i = 0;
	while (i < (*env).height)
	{
		j = 0;
		while (j < (*env).width)
		{
			tmpx = (*env).pgrid[i][j].x;
			tmpy = (*env).pgrid[i][j].y;
			(*env).pgrid[i][j].x = (2 * tmpy + tmpx) / 2;
			(*env).pgrid[i][j].y = (2 * tmpy - tmpx) / 2;
			j++;
		}
		i++;
	}
}

void	center_grid(void *param)
{
	int		i;
	int		j;
	int		diffx;
	int		diffy;
	t_env	*env;

	env = param;
	i = (*env).height / 2;
	j = (*env).width / 2;
	diffx = ((*env).wsz.x / 2) - (*env).pgrid[i][j].x;
	diffy = ((*env).wsz.y / 2) - (*env).pgrid[i][j].y;
	i = 0;
	while (i < (*env).height)
	{
		j = 0;
		while (j < (*env).width)
		{
			(*env).pgrid[i][j].x += diffx;
			(*env).pgrid[i][j].y += diffy;
			j++;
		}
		i++;
	}
}

void	put_grid(t_pos **grid, int height, int width, t_env env)
{
	int i;
	int j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (i != height - 1)
				print_seg(grid[i][j], grid[i + 1][j],
						convert_pos(env.value[i][j], env.value[i + 1][j]), env);
			if (j != width - 1)
				print_seg(grid[i][j], grid[i][j + 1],
						convert_pos(env.value[i][j], env.value[i][j + 1]), env);
			j++;
		}
		i++;
	}
}

void	move_grid(void *param, int mvx, int mvy)
{
	int		i;
	int		j;
	t_env	*env;

	env = param;
	i = 0;
	while (i < (*env).height)
	{
		j = 0;
		while (j < (*env).width)
		{
			(*env).pgrid[i][j].x += mvx;
			(*env).pgrid[i][j].y += mvy;
			j++;
		}
		i++;
	}
}
