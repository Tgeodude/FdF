/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeodude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:00:39 by tgeodude          #+#    #+#             */
/*   Updated: 2022/02/24 20:06:02 by tgeodude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "../MLX/mlx.h"
# include <fcntl.h>
# include "get_next_line.h"
# include "../libft/libft.h"
# include "../MLX/mlx.h"
# include "math.h"

typedef struct s_data {
	int			width;
	int			height;
	int			**map;
	void		*mlx_p;
	void		*mlx_w;
	void		*img;
	char		*addres;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			scale;
	int			color_1;
	int			color_2;
	int			color;
	int			x1;
	int			x2;
	int			y1;
	int			y2;
	int			z;
	int			z1;
	float		angle;
	int			position_x;
	int			position_y;
	int			flag_hook;
	int			signx;
	int			signy;
	int			deltay;
	int			deltax;
	int			error;
	int			error2;
	int			scale_z;
	int			count_z;
	float		angle_x;
	float		angle_y;
	float		angle_z;
	int			main_color;
	int			flag_map_color;
	int			flag_hex_map;
	int			**map_hex;
	int			x_1;
	int			y_1;
	int			x_2;
	int			y_2;
	int			size_color;
	int			s_c_c;
}	t_data;

void	map_create(char *file, t_data *fdf);
int		map_height(char *file);
int		map_width(char *file);
void	drawline(t_data *fdf);
void	angle(int *x, int *y, int z, t_data *fdf);
void	drawmap_color_and_scale(t_data *fdf);
void	drawmap_flag(int x, int y, int flag, t_data *fdf);
void	drawmap_pic(t_data *fdf);
void	movie_hook(int key, t_data *fdf);
int		key_hook(int key, t_data *fdf);
int		exit_hook(t_data *fdf);
void	drawmap(t_data *fdf);
void	validation_of_file(int argc, char **argv);
void	my_pixel_put(t_data *fdf, int x, int y, int color);
void	shift(t_data *data);
void	rotate_x(t_data *fdf);
void	rotate_y(t_data *fdf);
void	rotate_z(t_data *fdf);
int		dis_check(int x, int y);
int		check_map_color(t_data *fdf, char *s);
int		check_map_on_hex(char *book, t_data *fdf);
int		dec_hex_ab(char c);
int		dec_hex(char c);
int		convert_int(char *s, int size);
int		map_contein_color(char *s, int place);
void	map_parse(char *book, t_data *fdf);
int		color_or_hex(t_data *fdf, int x, int y);

#endif
