#include "fdf.h"

void drawLine(t_data *fdf) 
{

	fdf->deltaX = abs(fdf->x2 - fdf->x1);
	fdf->deltaY = abs(fdf->y2 - fdf->y1);
	fdf->signX = -1;
	fdf->signY = -1;
	if (fdf->x1 < fdf->x2)
		fdf->signX = 1;
	if (fdf->y1 < fdf->y2)
		fdf->signY = 1;
	fdf->error = fdf->deltaX - fdf->deltaY;
	mlx_pixel_put(fdf->mlx_pointer,fdf->mlx_window, fdf->x2, fdf->y2, fdf->color);
	while(fdf->x1 != fdf->x2 || fdf->y1 != fdf->y2)
	{
		mlx_pixel_put(fdf->mlx_pointer,fdf->mlx_window, fdf->x1, fdf->y1, fdf->color);
		fdf->error2 = fdf->error * 2;
		if (fdf->error2 > -fdf->deltaY)
		{
			fdf->error -= fdf->deltaY;
			fdf->x1 += fdf->signX;
		}
		if(fdf->error2 < fdf->deltaX)
		{
			fdf->error += fdf->deltaX;
			fdf->y1 += fdf->signY;
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
	if (fdf->z > 0 && fdf->z1 > 0)
		fdf->color = 0xd711d0;
	if ((fdf->z == 0 && fdf->z1 > 0) || (fdf->z > 0 && fdf->z1 == 0))
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
	fdf->x1 += fdf->position_x;
	fdf->x2 += fdf->position_x;	
	fdf->y1 -= fdf->position_y;
	fdf->y2 -= fdf->position_y;
	drawLine(fdf);
}

