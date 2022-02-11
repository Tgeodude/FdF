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
	   mlx_pixel_put(fdf.mlx_pointer,fdf.mlx_window, x2, y2, color);
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

int main(int argc, char **argv)
{
	t_data	fdf;
	int		fd;
	int	i;
	int	j;
	int	mp_wd;
	int	mp_hg;

	if (argc != 2)
		write(1, "error\n", 6);
	fd = open(argv[1], O_RDONLY);
	fdf = *(t_data *)malloc(sizeof(t_data));
	fdf.height = map_height(argv[1]);
	fdf.width = map_width(argv[1]);
	fdf.map = map_create(argv[1], fdf);
	close(fd);
	fdf.mlx_pointer = mlx_init();
	fdf.mlx_window = mlx_new_window(fdf.mlx_pointer, 1920, 1080, "Hello world");
	i = -1;
	mp_wd = fdf.width;
	mp_hg = fdf.height;
	fdf.height += 50 * (fdf.height);
	fdf.width += 50 * (fdf.width);
	while (i++, i < mp_wd)
	{
		j = -1;
		while (j++, j < mp_hg)
		{
			if (fdf.map[i][j] <=  0 && fdf.map[i][j + 1] && fdf.map[i][j + 1] > 0)
				drawLine(50 * i, 50 * j, 50 * i, (j + 1) * 50, fdf, 0x54ff05);
			if (fdf.map[i][j] <= 0 && fdf.map[i + 1][j] && fdf.map[i + 1][j] > 0)
				drawLine(50 * i, 50 * j, 50 * (i + 1), j * 50, fdf,0x54ff05);
			if (fdf.map[i][j] <= 0 && fdf.map[i + 1][j + 1] && fdf.map[i + 1][i + 1])
				drawLine(50 * i, 50 * j, 50 * (i + 1), (j + 1) * 50, fdf, 0x54ff05);
			if (fdf.map[i][j] > 0 && fdf.map[i][j + 1])
				drawLine(50 * i, 50 * j, 50 * i, (j + 1) * 50, fdf, 0x54ff05);
			if (fdf.map[i][j] > 0 && fdf.map[i + 1][j] && fdf.map[i + 1][j] > 0)
				drawLine(50 * i, 50 * j, 50 * (i + 1), j * 50, fdf, 0x54ff05);
			if (fdf.map[i][j] > 0 && fdf.map[i + 1][j + 1])
				drawLine(50 * i, 50 * j, 50 * (i + 1), (j + 1) * 50, fdf,0x54ff05);
			if (fdf.map[i][j] <= 0 && fdf.map[i][j + 1])
				drawLine(50 * i, 50 * j, 50 * i, (j + 1) * 50, fdf, 0xff052f);
		}
	}
	mlx_loop(fdf.mlx_pointer);
}
