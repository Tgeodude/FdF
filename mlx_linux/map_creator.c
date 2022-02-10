#include "fdf.h"

int	map_height(char	*maps)
{
	int		i;
	int		fd;
	char		*str;

	i = 0;
	fd = open(maps,O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		i++;
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (i);
}

int	map_width(char	*maps)
{
	char		*str;
	int		i;
	int		word;
	int		fd;

	i = 0;
	word = 0;
	fd = open(maps,O_RDONLY);
	str = get_next_line(fd);
	while (str[i])
	{
		while (str[i] == 40 && str[i])
			i++;
		if (str[i])
			word++;
		while (str[i] != 40 && str[i])
			i++;
	}
	close(fd);
	return (word);
}

int	**map_create(char *maps)
{
	int		**map;
	int		i;
	char		**str;
	int		j;
	int		fd;

	fd = open(maps,O_RDONLY);
	i = -1;
	map = (int **)malloc(sizeof(int *) * map_height(maps));
	while (i++, i < map_height(maps))
	{
		map[i] = (int *)malloc(sizeof(int) * map_width(maps));
		str = ft_split(get_next_line(fd), ' ');
		j = -1;
		while(j++, str[j])
			map[i][j] = ft_atoi(str[j]);
	}
	return (map);
}
