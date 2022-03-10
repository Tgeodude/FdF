/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeodude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:00:13 by tgeodude          #+#    #+#             */
/*   Updated: 2022/03/09 15:13:20 by tgeodude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	movie_hook(int key, t_data *fdf)
{
	if (key == 27 && fdf->scale > 3)
		fdf->scale /= 2;
	if (key == 24)
		fdf->scale *= 2;
	if (key == 123)
		fdf->position_x -= 100;
	if (key == 124)
		fdf->position_x += 100;
	if (key == 126)
		fdf->position_y += 100;
	if (key == 125)
		fdf->position_y -= 100;
	if (key == 33 && fdf->scale_z > 2)
		fdf->scale_z /= 2;
	if (key == 30)
		fdf->scale_z *= 2;
	if (key == 53)
	{
		mlx_destroy_window(fdf->mlx_p, fdf->mlx_w);
		exit(0);
	}
	if (key == 18)
		fdf->angle_x += 0.05;
	if (key == 19)
		fdf->angle_x -= 0.05;
	if (key == 20)
		fdf->angle_y += 0.05;
	if (key == 21)
		fdf->angle_y -= 0.05;
	if (key == 22)
		fdf->angle_z += 0.05;
	if (key == 23)
		fdf->angle_z -= 0.05;
	if (key == 256 && fdf->flag_rot == 1)
		fdf->flag_rot = 0;
	else if (key == 256 && fdf->flag_rot == 0)
		fdf->flag_rot = 1;
}

int	key_hook(int key, t_data *fdf)
{
	mlx_destroy_image(fdf->mlx_p, fdf->img);
	fdf->img = mlx_new_image(fdf->mlx_p, 2560, 1600);
	fdf->addres = mlx_get_data_addr(fdf->img, &fdf->bits_per_pixel, &fdf->line_length, &fdf->endian);
	movie_hook(key, fdf);
	if (fdf->flag_rot == 0)
		drawmap(fdf);
	if (fdf->flag_rot == 1)
		drawrotation(fdf);
	mlx_put_image_to_window(fdf->mlx_p, fdf->mlx_w, fdf->img, 0, 0);
	return (0);
}

int	exit_hook(t_data *fdf)
{
	mlx_destroy_window(fdf->mlx_p, fdf->mlx_w);
	exit(0);
}
