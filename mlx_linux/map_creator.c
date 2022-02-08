#include "fdf.h"

int	map_width(int fd)
{
	char	*str;
	int		i;

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
	int		i;

	str = get_next_line(fd);
	i = -1;
	while (i++, *str)
		str = get_next_line(fd);
	return (i);
}

int	**map_create(int fd)
{
	int		**map;
	int		i;
	char	**str;
	int		j;

	i = 0;
	map = (int **)malloc(sizeof(int *) * map_height(fd));
	while (i < map_height(fd))
	{
		map[i] = (int *)malloc(sizeof(int) * map_width(fd));
		str = ft_split(get_next_line(fd), ' ');
		j = -1;
		while(j++, str[j])
			map[i][j] = ft_atoi(str[j]);
	}
	return (map);
}
