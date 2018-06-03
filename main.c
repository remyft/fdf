#include "libft/libft.h"

int		main(int ac, char **av)
{
	int fd;
	char *lines;
	int i;

	i = 0;
	fd = open(av[1], O_RDONLY);
	while (get_next_line(fd, &lines) == 1)
	{
		ft_putstr(lines);
		ft_putchar('\n');
	}
	return (0);
}
