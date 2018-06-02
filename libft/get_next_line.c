/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rfontain <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/19 13:56:40 by rfontain          #+#    #+#             */
/*   Updated: 2018/06/01 20:45:58 by rfontain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					read_line(int fd, t_list *file)
{
	char	buff[BUFF_SIZE + 1];
	int		n;
	int		res;

	res = 0;
	while ((n = read(fd, buff, BUFF_SIZE)) > 0)
	{
		res += n;
		buff[n] = '\0';
		if (!(file->content = ft_strjoin(file->content, buff)))
			return (0);
		if (ft_occuc(buff, '\n'))
			break ;
	}
	return (1);
}

static t_list		*check_fd(int fd, t_list **file)
{
	t_list		*ret;

	ret = *file;
	while (ret)
	{
		if ((int)ret->content_size == fd)
			return (ret);
		ret = ret->next;
	}
	ret = ft_lstnew("\0", fd);
	ft_lstadd(file, ret);
	ret = *file;
	return (ret);
}

static char			*ft_realloc(char *str1, char *str2, int n)
{
	str1 = malloc(n + 1);
	*(str1 + n) = '\0';
	str1 = ft_strncpy(str1, str2, n);
	free(str2);
	return (str1);
}

int					get_next_line(const int fd, char **line)
{
	static t_list			*file;
	int						n;
	t_list					*current;
	char					*tmp;
	int						len;

	if (fd < 0 || line == NULL || read(fd, *line, 0) < 0)
		return (-1);
	current = check_fd(fd, &file);
	if (!(read_line(current->content_size, current)))
		return (-1);
	if (!(len = (int)ft_strlen(current->content)))
		return (0);
	*line = ft_strnew(1);
	n = ft_copyuntil(line, current->content, '\n');
	if (n < len)
	{
		tmp = malloc(len - (n + 1));
		tmp = ft_strcpy(tmp, (current->content + n + 1));
		free(current->content);
		current->content = ft_realloc(current->content, tmp, len - n - 1);
	}
	else
		ft_strclr(current->content);
	return (1);
}
