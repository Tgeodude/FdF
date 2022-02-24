#include "fdf.h"
#include <stdio.h>

void	drawMap(t_data *fdf)
{
	int	x;
	int	y;

	y = -1;
	while (y++, y < fdf->height)
	{
		x = -1;
		while (x++, x < fdf->width)
		{
			if (y + 1 < fdf->height)
			{
				drawMap_flag(x, y, 1, fdf);
				drawMap_pic(fdf);
			}
			if (x + 1 < fdf->width)
			{
				drawMap_flag(x, y, 0, fdf);
				drawMap_pic(fdf);
			}
		}
	}
}

int	maximum(int a, int b)
{
	if (a < b)
		return (b);
	return (a);
}

void	default_settings(t_data *fdf)
{
	fdf->scale = 750 / maximum(fdf->height, fdf->width);
	fdf->position_x = 500;
	fdf->position_y = -250;
	fdf->angle = 0.6;
}

void	movie_hook(int key, t_data *fdf)
{
	if (key == 45)
		fdf->scale /= 2;
	if (key == 61)
		fdf->scale *= 2;
	if (key == 65361)
		fdf->position_x -= 100;
	if (key == 65363)
		fdf->position_x += 100;
	if (key == 65362)
		fdf->position_y += 100;
	if (key == 65364)
		fdf->position_y -= 100;
	if (key == 32)
		fdf->angle += 0.1;
	if (key == 65507)
		fdf->angle = 0.6;
	if (key == 65307)
		mlx_destroy_window(fdf->mlx_pointer, fdf->mlx_window);
	if (fdf->flag_hook == 1)
		drawRotation(fdf);
	if (fdf->flag_hook == 0)
		drawMap(fdf);
}

int	key_hook(int key, t_data *fdf)
{
	printf("%d\n", key);
	mlx_clear_window(fdf->mlx_pointer, fdf->mlx_window);
	if (key == 65506 && fdf->flag_hook == 1)
	{
		fdf->flag_hook = 0;
		mlx_clear_window(fdf->mlx_pointer, fdf->mlx_window);
		drawMap(fdf);
	}
	else if (key == 65506 && fdf->flag_hook == 0)
	{
		fdf->flag_hook = 1;
		mlx_clear_window(fdf->mlx_pointer, fdf->mlx_window);
		drawRotation(fdf);
	}
	movie_hook(key, fdf);
	return (0);
}

int	exit_hook(t_data *fdf)
{
	mlx_destroy_window(fdf->mlx_pointer, fdf->mlx_window);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_data	fdf;
	int	fd;

	if (argc != 2)
	{
		write(1, "error\n", 6);
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	fdf = *(t_data *)malloc(sizeof(t_data));
	fdf.height = map_height(argv[1]);
	fdf.width = map_width(argv[1]);
	fdf.map = map_create(argv[1], fdf);
	default_settings(&fdf);
	close(fd);
	fdf.mlx_pointer = mlx_init();
	fdf.mlx_window = mlx_new_window(fdf.mlx_pointer, 1920, 1080, "FDF");
	fdf.flag_hook = 0;
	drawMap(&fdf);
	mlx_hook(fdf.mlx_window, 17, 0, exit_hook, &fdf);
	mlx_key_hook(fdf.mlx_window, key_hook, &fdf);
	mlx_loop(fdf.mlx_pointer);
}
