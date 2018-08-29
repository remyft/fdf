/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 22:57:40 by rfontain          #+#    #+#             */
/*   Updated: 2018/08/28 07:29:26 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include <stdio.h>

int		main(int ac, char **av)
{
	t_env	env;

	if (ac == 2)
	{
		env.fd = open(av[1], O_RDONLY);
		if (env.fd == -1)
			ft_puterror(1);
		env.iso = 0;
		env.pgrid = recup_grid(&env);
		if ((env.mlx = mlx_init()) == NULL)
			return (1);
		env.wsz = convert_pos(WIDTH - ((200 / env.width) * 40),
				HEIGHT - ((200 / env.height) * 40));
		printf("width : %d height : %d\n", env.wsz.x, env.wsz.y);
		if (env.wsz.x <= 1200 || env.wsz.y < 600)
			env.wsz = convert_pos(1400, 1100);
		if (!(env.win = mlx_new_window(env.mlx, env.wsz.x, env.wsz.y, "42")))
			return (1);
		center_grid(&env);
		put_grid(env.pgrid, env.height, env.width, env);
		mlx_key_hook(env.win, deal_key, &env);
		mlx_loop(env.mlx);
	}
	else
		ft_puterror(2);
	return (0);
}
