#include "fdf.h"
#include <stdio.h>
#include <math.h>

void drawLine(int x1, int y1, int x2, int y2, t_data fdf, int color) 
{
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY; 
    mlx_pixel_put(fdf.mlx_pointer,fdf.mlx_window, x2, y2, color);
	while(x1 != x2 || y1 != y2) 
   {
	   mlx_pixel_put(fdf.mlx_pointer,fdf.mlx_window, x1, y1, color);
        int error2 = error * 2;
        if(error2 > -deltaY) 
        {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX) 
        {
            error += deltaX;
            y1 += signY;
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
	fdf->scale = 700 / maximum(fdf->height, fdf->width);
}

int main(int argc, char **argv)
{
	t_data	fdf;
	int		fd;
	int	y;
	int	x;

	if (argc != 2)
		write(1, "error\n", 6);
	fd = open(argv[1], O_RDONLY);
	fdf = *(t_data *)malloc(sizeof(t_data));
	fdf.height = map_height(argv[1]);
	fdf.width = map_width(argv[1]);
	fdf.map = map_create(argv[1], fdf);
	default_settings(&fdf);
	close(fd);
	fdf.mlx_pointer = mlx_init();
	fdf.mlx_window = mlx_new_window(fdf.mlx_pointer, 1920, 1080, "Hello world");
	y = -1;
	while (y++, y < fdf.height)
	{
		x = -1;
		while (x++, x < fdf.width)
		{
			if (y + 1 < fdf.height)// отрисовка на плоскости 0 и на высоте
			{
				if (fdf.map[y][x] == 0 && fdf.map[y + 1][x] == 0)
					drawLine(x * fdf.scale, y * fdf.scale, x * fdf.scale, (y + 1) * fdf.scale, fdf, 0xf01114);
				if (fdf.map[y][x] > 0 && fdf.map[y + 1][x] > 0)
					drawLine(x * fdf.scale, y * fdf.scale, x * fdf.scale, (y + 1) * fdf.scale, fdf, 0xd711d0);
			}
			if (x + 1 < fdf.width)// отрисовка на плоскости 0 и на высоте
			{
				if (fdf.map[y][x] == 0 && fdf.map[y][x + 1] == 0)
					drawLine(x * fdf.scale, y * fdf.scale, (x + 1) * fdf.scale, y * fdf.scale, fdf, 0xf01114);
				if (fdf.map[y][x] > 0 && fdf.map[y][x + 1] > 0)
					drawLine(x * fdf.scale, y * fdf.scale, (x + 1) * fdf.scale, y * fdf.scale, fdf, 0xd711d0);
			}
			if (x + 1 < fdf.width && y + 1 < fdf.height) //отрисовка подъема и спуска
			{
				if (fdf.map[y][x] == 0 && fdf.map[y+1][x] > 0)
					drawLine(x * fdf.scale, y * fdf.scale, x * fdf.scale, (y + 1) * fdf.scale, fdf, 0x1cf011);
				if (fdf.map[y][x] == 0 && fdf.map[y][x + 1] > 0)
					drawLine(x * fdf.scale, y * fdf.scale, (x + 1) * fdf.scale, y * fdf.scale, fdf, 0x1cf011);
				if (fdf.map[y][x] > 0 && fdf.map[y + 1][x] == 0)
					drawLine(x * fdf.scale, y * fdf.scale, x * fdf.scale, (y + 1) * fdf.scale, fdf, 0x1cf011);
				if (fdf.map[y][x] > 0 && fdf.map[y][x + 1] == 0)
					drawLine(x * fdf.scale, y * fdf.scale, (x + 1) * fdf.scale, y * fdf.scale, fdf, 0x1cf011);
			}

		}
	}
	mlx_loop(fdf.mlx_pointer);
}
