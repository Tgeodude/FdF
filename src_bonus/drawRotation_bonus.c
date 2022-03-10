/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawRotation_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeodude <tgeodude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:09:31 by tgeodude          #+#    #+#             */
/*   Updated: 2022/03/10 20:10:57 by tgeodude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	color_or_hex_rot(t_data *fdf, int x, int y)
{
	if (fdf->flag_hex_map > 0 && fdf->flag_map_color)
		return (fdf->main_color);
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

void	drawmap_color_and_scale_rot(t_data *fdf)
{
	fdf->color_2 = color_or_hex_rot(fdf, fdf->x2, fdf->y2);
	fdf->color_1 = color_or_hex_rot(fdf, fdf->x1, fdf->y1);
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
	fdf->z *= (fdf->scale_z * (fdf->scale));
	fdf->z1 *= (fdf->scale_z * (fdf->scale));
}

void	drawmap_flag_rot(int x, int y, int flag, t_data *fdf)
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

void	drawmap_pic_rot(t_data *fdf)
{
	drawmap_color_and_scale(fdf);
	fdf->x1 += fdf->position_x;
	fdf->x2 += fdf->position_x;
	fdf->y1 -= fdf->position_y;
	fdf->y2 -= fdf->position_y;
	drawline(fdf);
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
				drawmap_flag_rot(x, y, 1, fdf);
				drawmap_pic_rot(fdf);
			}
			if (x + 1 < fdf->width)
			{
				drawmap_flag_rot(x, y, 0, fdf);
				drawmap_pic_rot(fdf);
			}
		}
	}
}
