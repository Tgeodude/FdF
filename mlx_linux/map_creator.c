#include <fdf.h>

int	map_width(int fd)
{
	char	*str;
	int	i;

	i = 0;
	str = get_next_line(fd);
	while (*str)
	{
		while (*str == ' ' && *str)
			str++;
		if (*str)
			i++;
		while (*str != ' ' && *str)
			i++;
	}
	return (i);
}

int	map_height(int fd)
{
	char	*str;
	int	i;

	str = get_next_line(fd);
	i = -1;
	while (i++, *str)
		str = get_next_line(fd);
	return (i);
}

int	**map_create(char *file)
{
	int	**map;
	int	fd;
	int	i;
	char	*str;

	fd = open(file,O_RDONLY);
	i = -1;
	map = (**int)malloc(sizeof(int *) * map_height(fd));
	while (++i < mp_hg)
	{
		map[i] = (int *)malloc(sizeof(int) * map_weight(fd));
		str = ft_split(get_next_line(fd), ' ');
	}
}
