#include "fdf.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	t_data *fdf;
	int		**map;
	int		fd;

	int	i;
	/*int	j;*/

	if (argc != 2)
		write(1, "error\n", 6);
	fd = open(argv[1], O_RDONLY);
	fdf = (t_data *)malloc(sizeof(t_data));
	map = map_create(fd);
	fdf->width = map_width(fd);
	fdf->height = map_height(fd);
	close(fd);

	i = 0;
	while(i++ < fdf->height)
	{
		j = 0;
		while (j++ < fdf->width)
			printf("%d", map[i][j]);
	}
	return (0);
}
