/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 23:09:57 by rfontain          #+#    #+#             */
/*   Updated: 2018/09/29 01:45:34 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static void	move_image(int key, void *param)
{
	t_env *env;

	env = param;
	mlx_clear_window((*env).mlx, (*env).win);
	if (key == 126)
		set_move(env, 0, -5);
	else if (key == 123)
		set_move(env, -5, 0);
	else if (key == 125)
		set_move(env, 0, 5);
	else if (key == 124)
		set_move(env, 5, 0);
	move_grid(param);
	put_grid((*env).pgrid, (*env).height, (*env).width, (*env));
}

static void	deal_image(int key, void *param)
{
	t_env	*env;

	env = param;
	mlx_clear_window((*env).mlx, (*env).win);
	if (key == 8 && (*env).iso)
		(*env).iso = 0;
	else if (key == 34 && !(*env).iso)
		(*env).iso = 1;
	else if (key == 15)
	{
		(*env).lenseg = 750 / (*env).width;
		reset_igrid((*env));
	}
	free_pgrid(env);
	env->pgrid = transform_to_pos(env->height, env->width, env->igrid, (*env));
	if ((*env).iso)
		cartoiso(param);
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
		zoom_image(param, (*env).mv_len);
		if ((*env).iso)
			cartoiso(param);
		center_grid(param);
	}
	if (key == 78)
	{
		zoom_image(param, -(*env).mv_len);
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
		change_height(param, 10);
	else
		change_height(param, -10);
	if ((*env).iso)
		cartoiso(param);
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
		free_env((*env), 1);
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
	{
		(*env).menu = ((*env).menu == 0) ? 1 : 0;
		mlx_clear_window((*env).mlx, (*env).win);
		put_grid((*env).pgrid, (*env).height, (*env).width, (*env));
	}
	else if (key >= 83 && key <= 92)
		(*env).mv_len = (key - 82) * 2;
	return (0);
}
