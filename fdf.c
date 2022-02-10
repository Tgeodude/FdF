#include "fdf.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	t_data	fdf;
	int		fd;
	int	i;
	int	j;

	if (argc != 2)
		write(1, "error\n", 6);
	fd = open(argv[1], O_RDONLY);
	fdf = *(t_data *)malloc(sizeof(t_data));
	fdf.height = map_height(argv[1]);
	fdf.width = map_width(argv[1]);
	fdf.map = map_create(argv[1], fdf);
	close(fd);
	fdf.mlx_pointer = mlx_init();

	i = -1;
	while(i++, i < fdf.height)
	{
		j = -1;
		while (j++, j < fdf.width)
			printf("%3d ", fdf.map[i][j]);
		printf("\n");
	}
}
