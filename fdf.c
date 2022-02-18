#include "fdf.h"
#include <math.h>
#include <stdio.h>

void drawLine(int x1, int y1, int x2, int y2, t_data *fdf, int color) 
{
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;
    int error = deltaX - deltaY; 
    mlx_pixel_put(fdf->mlx_pointer,fdf->mlx_window, x2, y2, color);
	while(x1 != x2 || y1 != y2) 
   {
	   mlx_pixel_put(fdf->mlx_pointer,fdf->mlx_window, x1, y1, color);
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

void	angle(int *x, int *y, int z, t_data *fdf)
{
	float	temp_x;
	float	temp_y;

	temp_x = *x;
	temp_y = *y;
	*x = (temp_x - temp_y) * cos(fdf->angle);
	*y = (temp_x + temp_y) * sin(fdf->angle) - z;
}


void	drawMap_color_and_scale(t_data *fdf)
{

	if (fdf->z == 0 && fdf->z1 == 0)
		fdf->color = 0xf01114;
	if (fdf->z > 0 && fdf->z1 == fdf->z && fdf->z < 25)
		fdf->color = 0xd711d0;
	if (fdf->z1 == fdf->z && fdf->z > 24)
		fdf->color = 0x1a0a0a;
	if ((fdf->z == 0 && fdf->z1 > 0) || (fdf->z > 0 && fdf->z1 == 0))
		fdf->color = 0x1cf011;
	if (fdf->z > 0 && fdf->z1 != fdf->z)
		fdf->color = 0x1cf011;
	if (fdf->z == 0 && fdf->z1 != fdf->z)
		fdf->color = 0x1cf011;
	fdf->x1 = (fdf->x1 * fdf->scale);
	fdf->x2 = (fdf->x2 * fdf->scale);
	fdf->y1 = (fdf->y1 * fdf->scale);
	fdf->y2 = (fdf->y2 * fdf->scale);
}

void	drawMap_flag(int x, int y, int flag, t_data *fdf)
{
	
	fdf->x1 = (x);
	fdf->y1 = (y);
	fdf->z = fdf->map[y][x];
	if (flag == 0)
	{
		fdf->x2 = (x + 1);
		fdf->y2 = (y);
		fdf->z1 = fdf->map[y][x + 1];
	}
	if (flag == 1)
	{
		fdf->x2 = (x);
		fdf->y2 = (y + 1);
		fdf->z1 = fdf->map[y + 1][x];
	}

}

void	drawMap_pic(t_data *fdf)
{
	drawMap_color_and_scale(fdf);
	angle(&fdf->x1,&fdf->y1, fdf->z, fdf);
	angle(&fdf->x2,&fdf->y2, fdf->z1, fdf);
	drawLine((fdf->x1 + fdf->position_x),(fdf->y1 - fdf->position_y),(fdf->x2 + fdf->position_x),(fdf->y2 - fdf->position_y), fdf, fdf->color);
}

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

int main(int argc, char **argv)
{
	t_data	fdf;
	int		fd;

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
	fdf.mlx_window = mlx_new_window(fdf.mlx_pointer, 1920, 1080, "FDF");
	fdf.flag_hook = 0;
	drawMap(&fdf);
	mlx_key_hook(fdf.mlx_window, key_hook, &fdf);
	mlx_loop(fdf.mlx_pointer);
}
