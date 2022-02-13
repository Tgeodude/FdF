#include "fdf.h"
#include <stdio.h>
#include <math.h>

/*char	calcul_hex(long long int val, char chr)
{
	if (val >= 10)
		return ((val - 10) + chr);
	return (val + '0');
}

int color_hex(int r, int g, int b)
{
	int *hex_color[8];
	int	i;
	int	val;


	hex_color[0] = 0;
	hex_color[1] = (int) "x";
	i = 1;
	while (i++, i < 8)
	{
		if (i < 4)
		{
			val = r % 16;
			r /= 16;
			hex_color[i] = (int)calcul_hex(val, 'a');
		}
	}
	return (int)(*hex_color);
}*/

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
	while (i++, i < mp_hg)
	{
		j = -1;
		while (j++, j < mp_wd)
		{
			if (i + 1 < mp_hg) //отрисовка плоскости на 0
			{
				if (fdf.map[i][j] == 0 && fdf.map[i + 1][j] == 0)
					drawLine(i * 50, j * 50, (i + 1) * 50,j * 50, fdf, 0xf50c27);
				if (fdf.map[i][j] > 0 && fdf.map[i + 1][j] > 0 )
					drawLine(i * 50, j * 50, (i + 1) * 50,j * 50, fdf, 0xd711d0);
			}
			if (j + 1 < mp_wd) //отрисока плоскости на 0
			{
				if (fdf.map[i][j] == 0 && fdf.map[i][j + 1] == 0)
					drawLine(i * 50, j * 50, i * 50,(j + 1) * 50, fdf, 0xf50c27);
				if (fdf.map[i][j] > 0 && fdf.map[i][j + 1] > 0)
					drawLine(i * 50, j * 50, i * 50,(j + 1) * 50, fdf, 0xd711d0);
			}
			if (i + 1 < mp_hg && j + 1 < mp_wd) //отрисовка плоскоти на высоте
			{
				if (fdf.map[i][j] == 0 && fdf.map[i + 1][j] > 0)
					drawLine(i * 50, j * 50, (i + 1) * 50,j * 50, fdf, 0x27f50c);
				if (fdf.map[i][j] == 0 && fdf.map[i][j + 1] > 0)
					drawLine(i * 50, j * 50, i * 50,(j + 1) * 50, fdf, 0x27f50c);
				if (fdf.map[i][j] > 0 && fdf.map[i + 1][j] == 0)
					drawLine(i * 50, j * 50, (i + 1) * 50,j * 50, fdf, 0x27f50c);
				if (fdf.map[i][j] > 0 && fdf.map[i][j + 1] == 0)
					drawLine(i * 50, j * 50, i * 50,(j + 1) * 50, fdf, 0x27f50c);
				if (fdf.map[i][j] == 0 && fdf.map[i + 1][j] == 0 && fdf.map[i][j + 1] == 0 && fdf.map[i + 1][j + 1] > 0)
					drawLine(i * 50, j * 50, (i + 1) * 50,(j + 1) * 50, fdf, 0x27f50c);
				if (fdf.map[i][j] > 0 && fdf.map[i + 1][j] == 0 && fdf.map[i][j + 1] == 0 && fdf.map[i + 1][j + 1] == 0)
					drawLine(i * 50, j * 50, (i + 1) * 50,(j + 1) * 50, fdf, 0x27f50c);
				if (fdf.map[i][j] == 0 && fdf.map[i + 1][j] > 0 && fdf.map[i][j + 1] > 0 && fdf.map[i + 1][j + 1] > 0)
					drawLine(i * 50, j * 50, (i + 1) * 50,(j + 1) * 50, fdf, 0x27f50c);
				if (fdf.map[i][j] == 0 && fdf.map[i + 1][j] == 0 && fdf.map[i][j + 1] > 0 && fdf.map[i + 1][j + 1] == 0)
					drawLine((i + 1) * 50,j * 50, i * 50, (j + 1) *50, fdf, 0x27f50c);
				if (fdf.map[i][j] == 0 && fdf.map[i + 1][j] > 0 && fdf.map[i][j + 1] == 0 && fdf.map[i + 1][j + 1] == 0)
					drawLine(i * 50,(j + 1) * 50, (i + 1) * 50, j *50, fdf, 0x27f50c);
				if (fdf.map[i][j] > 0 && fdf.map[i + 1][j] > 0 && fdf.map[i][j + 1] == 0 && fdf.map[i + 1][j + 1] > 0)
					drawLine(i* 50,(j + 1) * 50, (i + 1) * 50, j *50, fdf, 0x27f50c);
			}
		}
	}
	mlx_loop(fdf.mlx_pointer);
}
