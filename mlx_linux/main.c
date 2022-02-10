#include "fdf.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	t_data fdf;
	int	i;
	int	j;

	if (argc != 2)
		write(1, "error\n", 6);
	fdf = *(t_data *)malloc(sizeof(t_data));
	fdf.map = map_create(argv[1]);
	fdf.width = map_width(argv[1]);
	fdf.height = map_height(argv[1]);
	i = 0;
	while(i++ < fdf.height)
	{
		j = 0;
		while (j++ < fdf.width)
			printf("%d", fdf.map[i][j]);
	}
}
