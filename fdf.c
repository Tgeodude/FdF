/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeodude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 19:36:09 by tgeodude          #+#    #+#             */
/*   Updated: 2022/02/24 19:54:45 by tgeodude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

void	drawmap(t_data *fdf)
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
				drawmap_flag(x, y, 1, fdf);
				drawmap_pic(fdf);
			}
			if (x + 1 < fdf->width)
			{
				drawmap_flag(x, y, 0, fdf);
				drawmap_pic(fdf);
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

int	main(int argc, char **argv)
{
	t_data	fdf;
	int		fd;

	if (argc != 2)
	{
		write(1, "error\n", 6);
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	fdf = *(t_data *)malloc(sizeof(t_data));
	fdf.height = map_height(argv[1]);
	fdf.width = map_width(argv[1]);
	fdf.map = map_create(argv[1], fdf);
	default_settings(&fdf);
	close(fd);
	fdf.mlx_p = mlx_init();
	fdf.mlx_w = mlx_new_window(fdf.mlx_p, 1920, 1080, "FDF");
	fdf.flag_hook = 0;
	drawmap(&fdf);
	mlx_hook(fdf.mlx_w, 17, 0, exit_hook, &fdf);
	mlx_key_hook(fdf.mlx_w, key_hook, &fdf);
	mlx_loop(fdf.mlx_p);
}
