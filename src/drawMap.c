/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawMap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeodude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 19:49:50 by tgeodude          #+#    #+#             */
/*   Updated: 2022/02/24 20:05:06 by tgeodude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

void	drawline(t_data *fdf)
{
	fdf->deltax = abs(fdf->x2 - fdf->x1);
	fdf->deltay = abs(fdf->y2 - fdf->y1);
	fdf->signx = -1;
	fdf->signy = -1;
	if (fdf->x1 < fdf->x2)
		fdf->signx = 1;
	if (fdf->y1 < fdf->y2)
		fdf->signy = 1;
	fdf->error = fdf->deltax - fdf->deltay;
	if (dis_check(fdf->x2, fdf->y2) == 0)
		my_pixel_put(fdf, fdf->x2, fdf->y2, fdf->color_2);
	while (fdf->x1 != fdf->x2 || fdf->y1 != fdf->y2)
	{
		if (dis_check(fdf->x1, fdf->y1) == 0)
			my_pixel_put(fdf, fdf->x1, fdf->y1, fdf->color_1);
		fdf->error2 = fdf->error * 2;
		if (fdf->error2 > -fdf->deltay)
		{
			fdf->error -= fdf->deltay;
			fdf->x1 += fdf->signx;
		}
		if (fdf->error2 < fdf->deltax)
		{
			fdf->error += fdf->deltax;
			fdf->y1 += fdf->signy;
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

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	color_or_hex(t_data *fdf, int x, int y)
{
	if (fdf->flag_hex_map > 0 && fdf->flag_map_color)
		return(fdf->main_color);
	if (fdf->flag_hex_map == 1 && !fdf->flag_map_color)
		return (fdf->map_hex[y][x]);
	if (fdf->z == 0 && fdf->z1 == 0)
		return (0xff0000);
	if ((fdf->z > 0 && fdf->z1 > 0) || (fdf->z < 0 && fdf->z1 < 0))
		return (0xd711d0);
	if ((fdf->z == 0 && fdf->z1 > 0) || (fdf->z > 0 && fdf->z1 == 0))
		return (0x1cf011);
	if ((fdf->z == 0 && fdf->z1 < 0) || (fdf->z < 0 && fdf->z1 == 0))
		return (0x1cf011);
	if ((fdf->z > 0 && fdf->z1 < 0) || (fdf->z < 0 && fdf->z1 > 0))
		return (0x1cf011);
	return (0);
}

void	drawmap_color_and_scale(t_data *fdf)
{
	fdf->color_2 = color_or_hex(fdf, fdf->x2, fdf->y2);
	fdf->color_1 = color_or_hex(fdf, fdf->x1, fdf->y1);
	fdf->y_1 = fdf->y1;
	fdf->y_2 = fdf->y2;
	fdf->x1 = (fdf->x1 * fdf->scale);
	fdf->x2 = (fdf->x2 * fdf->scale);
	fdf->y1 = (fdf->y1 * fdf->scale);
	fdf->y2 = (fdf->y2 * fdf->scale);
	if (fdf->z <= 100 && fdf->z >= -100)
		if ((fdf->z >= 50 || fdf->z <= -50))
			fdf->z /= 2;
	if (fdf->z1 <= 100 && fdf->z1 >= -100)
		if ((fdf->z1 >= 50 || fdf->z1 <= -50))
			fdf->z1 /= 2;
	if (!(fdf->z >= -9 && fdf->z <= 9))
		fdf->z /= 10;
	if (!(fdf->z1 >= -9 && fdf->z1 <= 9))
		fdf->z1 /= 10;
	fdf->z = (fdf->z * (fdf->scale));
	fdf->z1 = (fdf->z1 * (fdf->scale));
	shift(fdf);
}
void	drawmap_flag(int x, int y, int flag, t_data *fdf)
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

void	drawmap_pic(t_data *fdf)
{
	drawmap_color_and_scale(fdf);
	angle(&fdf->x1, &fdf->y1, fdf->z, fdf);
	angle(&fdf->x2, &fdf->y2, fdf->z1, fdf);
	fdf->x1 += fdf->position_x;
	fdf->x2 += fdf->position_x;
	fdf->y1 -= fdf->position_y;
	fdf->y2 -= fdf->position_y;
	drawline(fdf);
}
