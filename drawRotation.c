/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawRotation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeodude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 19:59:22 by tgeodude          #+#    #+#             */
/*   Updated: 2022/02/24 20:04:33 by tgeodude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

void	drawrotation_line(t_data *fdf, int color)
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
	mlx_pixel_put(fdf->mlx_p, fdf->mlx_w, fdf->x2, fdf->y2, color);
	while (fdf->x1 != fdf->x2 || fdf->y1 != fdf->y2)
	{
		mlx_pixel_put(fdf->mlx_p, fdf->mlx_w, fdf->x1, fdf->y1, color);
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

void	drawrotation_color_and_scale(t_data *fdf)
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

void	drawrotation_flag(int x, int y, int flag, t_data *fdf)
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

void	drawrotation_pic(t_data *fdf)
{
	drawrotation_color_and_scale(fdf);
	fdf->x1 += fdf->position_x;
	fdf->x2 += fdf->position_x;
	fdf->y1 -= fdf->position_y;
	fdf->y2 -= fdf->position_y;
	drawrotation_line(fdf, fdf->color);
}

void	drawrotation(t_data *fdf)
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
				drawrotation_flag(x, y, 1, fdf);
				drawrotation_pic(fdf);
			}
			if (x + 1 < fdf->width)
			{
				drawrotation_flag(x, y, 0, fdf);
				drawrotation_pic(fdf);
			}
		}
	}
}
