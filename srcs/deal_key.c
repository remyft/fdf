/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 23:09:57 by rfontain          #+#    #+#             */
/*   Updated: 2018/08/28 07:03:21 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include <stdio.h>

static void	move_image(int key, void *param)
{
	t_env *env;

	env = param;
	mlx_clear_window((*env).mlx, (*env).win);
	if (key == 126)
		move_grid(param, 0, -20);
	if (key == 123)
		move_grid(param, -20, 0);
	if (key == 125)
		move_grid(param, 0, 20);
	if (key == 124)
		move_grid(param, 20, 0);
	put_grid((*env).pgrid, (*env).height, (*env).width, (*env));
}

static void	deal_image(int key, void *param)
{
	t_env *env;

	env = param;
	mlx_clear_window((*env).mlx, (*env).win);
	if (key == 8 && (*env).iso)
	{
		isotocar(param);
		center_grid(param);
		(*env).iso = 0;
	}
	else if (key == 34 && !(*env).iso)
	{
		cartoiso(param);
		center_grid(param);
		(*env).iso = 1;
	}
	else if (key == 15)
		center_grid(param);
	put_grid((*env).pgrid, (*env).height, (*env).width, (*env));
}

static void	image_zoom(int key, void *param)
{
	t_env	*env;

	env = param;
	mlx_clear_window((*env).mlx, (*env).win);
	if (key == 69)
	{
		zoom_image(param, 10);
		if ((*env).iso)
			cartoiso(param);
		center_grid(param);
	}
	if (key == 78)
	{
		zoom_image(param, -10);
		if ((*env).iso)
			cartoiso(param);
		center_grid(param);
	}
	put_grid((*env).pgrid, (*env).height, (*env).width, (*env));
}

static void	height_change(int key, void *param)
{
	t_env *env;

	env = param;
	mlx_clear_window((*env).mlx, (*env).win);
	if (key == 32)
	{
		change_height(param, 10);
		if ((*env).iso)
			cartoiso(param);
	}
	else
	{
		change_height(param, -10);
		if ((*env).iso)
			cartoiso(param);
	}
	center_grid(param);
	put_grid((*env).pgrid, (*env).height, (*env).width, (*env));
}

int			deal_key(int key, void *param)
{
	t_env *env;

	env = param;
	if (key == 53)
	{
		mlx_destroy_window((*env).mlx, (*env).win);
		exit(0);
	}
	if (key == 34 || key == 8 || key == 15)
		deal_image(key, param);
	else if (key == 123 || key == 124 || key == 125 || key == 126)
		move_image(key, param);
	else if (key == 69 || key == 78)
		image_zoom(key, param);
	else if (key == 32 || key == 2)
		height_change(key, param);
	else if (key == 46)
		put_menu(param);
	return (0);
}
