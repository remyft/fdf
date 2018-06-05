/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 23:10:00 by rfontain          #+#    #+#             */
/*   Updated: 2018/06/05 17:25:02 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/libft.h"
# include <mlx.h>
# include <unistd.h>

# define LEN_SEG 50
# define WIDTH 1600
# define HEIGHT 900

typedef struct	s_pos
{
	int			x;
	int			y;
	int			value;
}				t_pos;

typedef struct	s_grid
{
	t_pos		**tab;
	int			height;
	int			width;
}				t_grid;

typedef struct	s_data
{
	void		*mlx;
	void		*win;
	t_grid		grid;
}				t_data;

t_grid			ft_stoii(char **lines);
t_pos			**ft_iitotpos(int height, int width, int **tab);
int				ft_widthtab(char *tab);

void			ft_putgrid(t_grid grid, void *param);
void			ft_initimage(t_grid grid);
void			ft_movegrid(t_grid grid, int x, int y);
void			ft_ytrans(t_grid grid, int height, int width, int z);
void			ft_xtrans(t_grid grid, int height, int width, int z);
void			ft_xrot(t_grid grid, int height, int width, int z);

void			ft_diffint(int *x, int *y, t_grid grid);
void			ft_printseg(int x1, int y1, int x2, int y2, void *param);

int				deal_key(int key, void *param);

#endif
