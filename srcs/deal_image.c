/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 18:21:53 by rfontain          #+#    #+#             */
/*   Updated: 2018/09/27 17:55:07 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_pos	*get_extrem(t_env env)
{
	t_pos	*extrem;
	int		i;
	int		j;

	if ((extrem = (t_pos*)malloc(sizeof(t_pos) * 2)) == NULL)
		return (NULL);
	extrem[0] = c_pos(env.pgrid[0][0].x, env.pgrid[0][0].x);
	extrem[1] = c_pos(env.pgrid[0][0].y, env.pgrid[0][0].y);
	i = -1;
	while (++i < env.height)
	{
		j = -1;
		while (++j < env.width)
		{
			if (env.pgrid[i][j].x < extrem[0].x)
				extrem[0].x = env.pgrid[i][j].x;
			if (env.pgrid[i][j].x > extrem[0].y)
				extrem[0].y = env.pgrid[i][j].x;
			if (env.pgrid[i][j].y < extrem[1].x)
				extrem[1].x = env.pgrid[i][j].y;
			if (env.pgrid[i][j].y > extrem[1].y)
				extrem[1].y = env.pgrid[i][j].y;
		}
	}
	return (extrem);
}

void	center_grid(void *param)
{
	int		i;
	int		j;
	t_pos	*ext;
	t_pos	diff;
	t_env	*env;

	env = param;
	i = (*env).height / 2;
	j = (*env).width / 2;
	if (!(ext = get_extrem((*env))))
		return ;
	diff.x = ((*env).wsz.x / 2) - ext[0].x - ((ext[0].y - ext[0].x) / 2);
	diff.y = ((*env).wsz.y / 2) - ext[1].x - ((ext[1].y - ext[1].x) / 2);
	i = -1;
	while (++i < (*env).height)
	{
		j = -1;
		while (++j < (*env).width)
		{
			(*env).pgrid[i][j].x += diff.x;
			(*env).pgrid[i][j].y += diff.y;
		}
	}
	free(ext);
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
						c_pos(env.value[i][j], env.value[i + 1][j]), env);
			if (j != width - 1)
				print_seg(grid[i][j], grid[i][j + 1],
						c_pos(env.value[i][j], env.value[i][j + 1]), env);
			j++;
		}
		i++;
	}
	if (env.menu)
		put_menu(&env);
}

int		move_grid(void *param)
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
			(*env).pgrid[i][j].x += (*env).mvx;
			(*env).pgrid[i][j].y += (*env).mvy;
			j++;
		}
		i++;
	}
	return (0);
}
