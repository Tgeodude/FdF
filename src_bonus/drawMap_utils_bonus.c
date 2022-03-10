/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawMap_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeodude <tgeodude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:11:47 by tgeodude          #+#    #+#             */
/*   Updated: 2022/03/10 20:11:53 by tgeodude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	settings_draw(t_data *fdf)
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
}

void	drawline(t_data *fdf)
{
	settings_draw(fdf);
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

void	drawline_rot(t_data *fdf)
{
	settings_draw(fdf);
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
