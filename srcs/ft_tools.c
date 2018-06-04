/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/04 23:07:38 by rfontain          #+#    #+#             */
/*   Updated: 2018/06/04 23:24:12 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int		ft_widthtab(char *tab)
{
	int i;
	int res;

	res = 0;
	i = 0;
	while (tab[i])
	{
		if (ft_isdigit(tab[i]))
		{
			res++;
			while (ft_isdigit(tab[i]))
				i++;
		}
		else
			i++;
	}
	return (res);
}

t_pos	**ft_iitotpos(int height, int width, int **tab)
{
	int i;
	int j;
	int xec;
	int yec;
	t_pos **ret;

	i = 0;
	yec = 0;
	ret = (t_pos**)malloc(sizeof(t_pos*) * height);
	while (i < height)
	{
		j = 0;
		xec = 0;
		ret[i] = (t_pos*)malloc(sizeof(t_pos) * width);
		while (j < width)
		{
			ret[i][j].x = xec;
			xec += LEN_SEG;
			ret[i][j].y = yec;
			ret[i][j].value = tab[i][j];
			j++;
		}
		yec += LEN_SEG;
		i++;
	}
	return (ret);
}

t_grid	ft_stoii(char **lines)
{
	t_grid	grid;
	int		**tab;
	char	tmp[32];
	int		i;
	int		j;
	int		k;
	int		l;

	grid.height = 0;
	i = 0;
	while (lines[grid.height])
		grid.height++;
	tab = (int**)malloc(sizeof(int*) * grid.height);
	grid.width = ft_widthtab(lines[0]);
	while (i < grid.height)
	{
		j = 0;
		tab[i] = (int*)malloc(sizeof(int) * grid.width);
		l = 0;
		while (l < grid.width)
		{
			if (ft_isdigit(lines[i][j]))
			{
				k = 0;
				while (ft_isdigit(lines[i][j]))
					tmp[k++] = lines[i][j++];
				tmp[k] = '\0';
				tab[i][l++] = ft_atoi(tmp);
			}
			else
				j++;
		}
		i++;
	}
	grid.tab = ft_iitotpos(grid.height, grid.width, tab);
	return (grid);
}
