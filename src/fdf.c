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
	fdf->scale = 550 / maximum(fdf->height, fdf->width);
	fdf->position_x = 750;
	fdf->position_y = -300;
	fdf->angle = 0.6;
	fdf->angle_x = 0;
	fdf->angle_y = 0;
	fdf->angle_z = 0;
}

int	main(int argc, char **argv)
{
	t_data	fdf;
	int		fd;
	
	fdf = *(t_data *)malloc(sizeof(t_data));
	fdf.height = map_height(argv[1]);
	fdf.width = map_width(argv[1]);
	map_create(argv[1], &fdf);
	validation_of_file(argc, argv);
	fd = open(argv[1], O_RDONLY);
    fdf.flag_map_color = 0;
    fdf.main_color = 0;
	/*fdf.flag_hex_map = check_map_on_hex(argv[1], &fdf);
	if (fdf.flag_hex_map == 1 && !fdf.flag_map_color)
        map_parse(argv[1], &fdf);
    if (fdf.flag_hex_map > 1 && fdf.flag_map_color)
        fdf.main_color = fdf.flag_hex_map;*/
	default_settings(&fdf);
	close(fd);
	fdf.mlx_p = mlx_init();
	fdf.mlx_w = mlx_new_window(fdf.mlx_p, 2560, 1600, "FDF");
	fdf.img = mlx_new_image(fdf.mlx_p, 2560, 1600);
	fdf.addres = mlx_get_data_addr(fdf.img, &fdf.bits_per_pixel, &fdf.line_length, &fdf.endian);
	fdf.flag_hook = 0;
	drawmap(&fdf);
	mlx_put_image_to_window(fdf.mlx_p, fdf.mlx_w, fdf.img, 0, 0);
	mlx_hook(fdf.mlx_w, 2, 0, key_hook, &fdf);
	mlx_loop(fdf.mlx_p);
}
