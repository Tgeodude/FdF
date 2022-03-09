
#include "fdf_bonus.h"

void	my_pixel_put(t_data *fdf, int x, int y, int color)
{
	char	*dst;

	dst = fdf->addres + (y * fdf->line_length + x * (fdf->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	shift(t_data *fdf)
{
	rotate_x(fdf);
	rotate_y(fdf);
	rotate_z(fdf);
}

void	rotate_x(t_data *fdf)
{
	float	temp_y;

	temp_y = fdf->y1;
	fdf->y1 = (int)(temp_y * cos(fdf->angle_x) + \
					fdf->z * sin(fdf->angle_x));
	fdf->z = (int)(-temp_y * sin(fdf->angle_x) + \
					fdf->z * cos(fdf->angle_x));
	temp_y = fdf->y2;
	fdf->y2 = (int)(temp_y * cos(fdf->angle_x) + \
					fdf->z1 * sin(fdf->angle_x));
	fdf->z1 = (int)(-temp_y * sin(fdf->angle_x) + \
					fdf->z1 * cos(fdf->angle_x));
}

void	rotate_y(t_data *fdf)
{
	float	temp_x;

	temp_x = fdf->x1;
	fdf->x1 = (int)(temp_x * cos(fdf->angle_y) + \
					fdf->z * sin(fdf->angle_y));
	fdf->z = (int)(-temp_x * sin(fdf->angle_y) + \
					fdf->z * cos(fdf->angle_y));
	temp_x = fdf->x2;
	fdf->x2 = (int)(temp_x * cos(fdf->angle_y) + \
					fdf->z1 * sin(fdf->angle_y));
	fdf->z1 = (int)(-temp_x * sin(fdf->angle_y) + \
					fdf->z1 * cos(fdf->angle_y));
}

void	rotate_z(t_data *fdf)
{
	float	temp_x;
	float	temp_y;

	temp_x = fdf->x1;
	temp_y = fdf->y1;
	fdf->x1 = (int)(temp_x * cos(fdf->angle_z) - temp_y * sin(fdf->angle_z));
	fdf->y1 = (int)(temp_x * sin(fdf->angle_z) + temp_y * cos(fdf->angle_z));
	temp_x = fdf->x2;
	temp_y = fdf->y2;
	fdf->x2 = (int)(temp_x * cos(fdf->angle_z) - temp_y * sin(fdf->angle_z));
	fdf->y2 = (int)(temp_x * sin(fdf->angle_z) + temp_y * cos(fdf->angle_z));
}

int	dis_check(int x, int y)
{
	if (x >= 2560 || y >= 1600)
		return (-1);
	if (x < 0 || y < 0)
		return (-1);
	return (0);
}
