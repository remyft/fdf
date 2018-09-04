/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/28 02:40:42 by rfontain          #+#    #+#             */
/*   Updated: 2018/09/01 15:49:35 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_pos	c_pos(int col1, int col2)
{
	t_pos	col;

	col.x = col1;
	col.y = col2;
	return (col);
}

int		**set_value(t_env env, int **value)
{
	int i;
	int j;

	value = (int**)malloc(sizeof(int*) * env.height);
	i = 0;
	while (i < env.height)
	{
		j = 0;
		value[i] = (int*)malloc(sizeof(int*) * env.width);
		while (j < env.width)
		{
			value[i][j] = env.igrid[i][j];
			j++;
		}
		i++;
	}
	return (value);
}

void	ft_puterror(int n)
{
	if (n == 1)
	{
		ft_putstr("Le fichier rentre est invalide ; vous n'en avez pas les ");
		ft_putstr("droits ou il n'existe pas.");
	}
	else if (n == 0)
		ft_putstr("Le fichier est vide.");
	else if (n == 2)
		ft_putstr("Vous devez rentrer un fichier et seulement un.");
	else
		ft_putstr("Une erreur a eu lieu.");
	ft_putchar('\n');
	exit(2);
}

void	put_menu(void *param)
{
	t_env	*env;
	char	*str;

	env = param;
	str = "i : cartesian to isometric";
	mlx_string_put((*env).mlx, (*env).win, 10, 10, 0xFFFFFF, str);
	str = "c : isometric to cartesian";
	mlx_string_put((*env).mlx, (*env).win, 10, 30, 0xFFFFFF, str);
	mlx_string_put((*env).mlx, (*env).win, 10, 50, 0xFFFFFF, "+ : zoom +");
	mlx_string_put((*env).mlx, (*env).win, 10, 70, 0xFFFFFF, "- : zoom -");
	str = "arrow keys : move the figure";
	mlx_string_put((*env).mlx, (*env).win, 10, 90, 0xFFFFFF, str);
	str = "r : reset position";
	mlx_string_put((*env).mlx, (*env).win, 10, 110, 0xFFFFFF, str);
	mlx_string_put((*env).mlx, (*env).win, 10, 130, 0xFFFFFF, "u : height +");
	mlx_string_put((*env).mlx, (*env).win, 10, 150, 0xFFFFFF, "d : height -");
	print_seg(c_pos(5, 5), c_pos(295, 5), c_pos(10, 10), (*env));
	print_seg(c_pos(5, 175), c_pos(295, 175), c_pos(10, 10), (*env));
	print_seg(c_pos(5, 5), c_pos(5, 175), c_pos(10, 10), (*env));
	print_seg(c_pos(295, 5), c_pos(295, 175), c_pos(10, 10), (*env));
}

void	set_move(t_env *env, int mvx, int mvy)
{
	(*env).mvx = mvx * (*env).mv_len;
	(*env).mvy = mvy * (*env).mv_len;
}
