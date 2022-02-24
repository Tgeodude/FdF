/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeodude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:00:13 by tgeodude          #+#    #+#             */
/*   Updated: 2022/02/24 20:00:15 by tgeodude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

void	movie_hook(int key, t_data *fdf)
{
	if (key == 27)
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
	if (key == 49)
		fdf->angle += 0.1;
	if (key == 256)
		fdf->angle = 0.6;
	if (key == 53)
	{
		mlx_destroy_window(fdf->mlx_p, fdf->mlx_w);
		exit(0);
	}
	if (fdf->flag_hook == 1)
		drawrotation(fdf);
	if (fdf->flag_hook == 0)
		drawmap(fdf);
}

int	key_hook(int key, t_data *fdf)
{
	mlx_clear_window(fdf->mlx_p, fdf->mlx_w);
	if (key == 258 && fdf->flag_hook == 1)
	{
		fdf->flag_hook = 0;
		mlx_clear_window(fdf->mlx_p, fdf->mlx_w);
		drawmap(fdf);
	}
	else if (key == 258 && fdf->flag_hook == 0)
	{
		fdf->flag_hook = 1;
		mlx_clear_window(fdf->mlx_p, fdf->mlx_w);
		drawrotation(fdf);
	}
	movie_hook(key, fdf);
	return (0);
}

int	exit_hook(t_data *fdf)
{
	mlx_destroy_window(fdf->mlx_p, fdf->mlx_w);
	exit(0);
}
