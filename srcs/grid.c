/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/26 12:27:12 by rfontain          #+#    #+#             */
/*   Updated: 2018/09/29 01:49:48 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int		width_tab(char *line)
{
	int		width;
	int		i;

	i = 0;
	width = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]))
		{
			width++;
			while (ft_isdigit(line[i]))
				i++;
		}
		else
			i++;
	}
	return (width);
}

static int		recup_int(char *line, int *l)
{
	char	tmp[32];
	int		k;

	k = 0;
	while (ft_isdigit(line[(*l)]))
		tmp[k++] = line[(*l)++];
	tmp[k] = '\0';
	return (ft_atoi(tmp));
}

static int		**transform_grid(int width, int height, char **lines)
{
	int		**tab;
	int		i;
	int		j;
	int		l;

	if ((tab = (int**)malloc(sizeof(int*) * height)) == NULL)
		ft_puterror(4);
	i = -1;
	while (++i < height)
	{
		j = 0;
		l = 0;
		if ((tab[i] = (int*)malloc(sizeof(int) * width)) == NULL)
			ft_puterror(4);
		while (j < width)
		{
			if (ft_isdigit(lines[i][l]))
				tab[i][j++] = recup_int(lines[i], &l);
			l++;
		}
		free(lines[i]);
	}
	return (tab);
}

t_pos			**transform_to_pos(int height, int width, int **tab, t_env env)
{
	int		i;
	int		j;
	t_pos	pos;
	t_pos	**ret;

	i = -1;
	pos.y = 0;
	if (!(ret = (t_pos**)malloc(sizeof(t_pos*) * height)))
		ft_puterror(4);
	while (++i < height)
	{
		j = -1;
		pos.x = 0;
		if (!(ret[i] = (t_pos*)malloc(sizeof(t_pos) * width)))
			ft_puterror(4);
		while (++j < width)
		{
			ret[i][j].x = (pos.x - tab[i][j]);
			pos.x += env.lenseg;
			ret[i][j].y = (pos.y - tab[i][j]);
			ret[i][j].value = tab[i][j];
		}
		pos.y += env.lenseg;
	}
	return (ret);
}

t_pos			**recup_grid(t_env *env)
{
	char	*lines[1000];
	int		i;

	i = 0;
	while (get_next_line((*env).fd, &lines[i]) == 1)
		i++;
	if (i == 0)
		ft_puterror(0);
	lines[i] = NULL;
	(*env).height = i;
	i = 0;
	(*env).width = width_tab(lines[0]);
	while (lines[++i])
		if (width_tab(lines[i]) != (*env).width)
			return (NULL);
	(*env).igrid = transform_grid((*env).width, (*env).height, lines);
	(*env).value = set_value((*env), (*env).igrid);
	(*env).lenseg = 750 / (*env).width;
	env->wsz = c_pos(WIDTH - ((200 / env->width) * 40),
			HEIGHT - ((200 / env->height) * 40));
	if (env->wsz.x <= 1200 || env->wsz.y < 600)
		env->wsz = c_pos(1400, 1100);
	return (transform_to_pos((*env).height, (*env).width, (*env).igrid,
				(*env)));
}
