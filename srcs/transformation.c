/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/31 08:47:04 by rfontain          #+#    #+#             */
/*   Updated: 2018/09/28 18:35:54 by rfontain         ###   ########.fr       */
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

# include <stdio.h>

void	zoom_image(void *param, int zoom)
{
	t_env	*env;
	int		i;
	int		j;

	env = param;
	i = 0;
	if ((*env).lenseg + zoom > 0)
		(*env).lenseg += zoom;
	else
		(*env).lenseg = 1;
	while (i < env->height)
	{
		j = 0;
		while (j < env->width)
		{
			env->igrid[i][j] = 0;
			j++;
		}
		i++;
	}
	(*env).pgrid = transform_to_pos((*env).height, (*env).width, (*env).igrid,
			(*env));
}
