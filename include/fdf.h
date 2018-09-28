/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/30 22:55:30 by rfontain          #+#    #+#             */
/*   Updated: 2018/09/29 01:44:44 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include <mlx.h>

# define WIDTH 2000
# define HEIGHT 1500
# define LEN_SEG 50

typedef struct	s_pos
{
	int			x;
	int			y;
	int			value;
}				t_pos;

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	int			fd;
	int			**igrid;
	int			**value;
	t_pos		**pgrid;
	t_pos		wsz;
	char		*name;
	int			iso;
	int			lenseg;
	int			width;
	int			height;
	int			menu;
	int			mvx;
	int			mvy;
	int			mv_len;
}				t_env;

int				set_struct(t_env *env, char *name);
void			free_pgrid(t_env *env);

int				deal_key(int key, void *param);

t_pos			**recup_grid(t_env *env);
t_pos			**transform_to_pos(int height, int width, int **tab,
		t_env env);

void			print_seg(t_pos pos1, t_pos pos2, t_pos col, t_env env);
void			change_height(void *param, int hg);
void			free_env(t_env env, int ex);

void			center_grid(void *param);
void			put_grid(t_pos **grid, int height, int width, t_env env);
int				move_grid(void *param);
void			reset_igrid(t_env env);

t_pos			c_pos(int col1, int col2);
int				**set_value(t_env env, int **value);
void			ft_puterror(int n);
void			put_menu(void *param);
void			set_move(t_env *env, int mvx, int mvy);

void			cartoiso(void *param);
void			isotocar(void *param);
void			zoom_image(void *paran, int zoom);

#endif
