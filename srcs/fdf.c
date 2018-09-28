/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 22:57:40 by rfontain          #+#    #+#             */
/*   Updated: 2018/09/29 01:44:26 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	free_pgrid(t_env *env)
{
	int i;

	i = -1;
	while (++i < env->height)
		free(env->pgrid[i]);
	free(env->pgrid);
}

int		set_struct(t_env *env, char *name)
{
	env->fd = open(name, O_RDONLY);
	if (env->fd == -1)
		ft_puterror(1);
	env->iso = 0;
	env->menu = 0;
	env->mv_len = 5;
	if (!(env->pgrid = recup_grid(env)))
		ft_puterror(3);
	if ((env->mlx = mlx_init()) == NULL)
		return (1);
	if (!(env->win = mlx_new_window(env->mlx, env->wsz.x, env->wsz.y, "42")))
		return (1);
	env->name = ft_strdup(name);
	return (0);
}

int		main(int ac, char **av)
{
	t_env	env;

	if (ac == 2)
	{
		if (set_struct(&env, av[1]))
			ft_puterror(4);
		if (env.height > 1 && env.width > 1)
		{
			center_grid(&env);
			put_grid(env.pgrid, env.height, env.width, env);
			mlx_hook(env.win, 2, 0, deal_key, &env);
			mlx_loop(env.mlx);
		}
	}
	else
		ft_puterror(2);
	return (0);
}
