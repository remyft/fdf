/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 22:57:40 by rfontain          #+#    #+#             */
/*   Updated: 2018/09/19 03:38:48 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static int	set_struct(t_env *env, char **av)
{
	env->fd = open(av[1], O_RDONLY);
	if (env->fd == -1)
		ft_puterror(1);
	env->iso = 0;
	env->menu = 0;
	env->mv_len = 5;
	env->pgrid = recup_grid(env);
	if ((env->mlx = mlx_init()) == NULL)
		return (1);
	if (!(env->win = mlx_new_window(env->mlx, env->wsz.x, env->wsz.y, "42")))
		return (1);
	return (0);
}

int			main(int ac, char **av)
{
	t_env	env;

	if (ac == 2)
	{
		if (set_struct(&env, av))
			ft_puterror(3);
		center_grid(&env);
		put_grid(env.pgrid, env.height, env.width, env);
		mlx_key_hook(env.win, deal_key, &env);
		mlx_loop(env.mlx);
	}
	else
		ft_puterror(2);
	return (0);
}
