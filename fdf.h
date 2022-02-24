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
# include <mlx.h>
# include <fcntl.h>
# include "get_next_line.h"
# include "libft/libft.h"
# include <mlx.h>
# include "math.h"

typedef struct s_data {
	int		width;
	int		height;
	int		**map;
	void	*mlx_p;
	void	*mlx_w;
	int		scale;
	int		color;
	int		x1;
	int		x2;
	int		y1;
	int		y2;
	int		z;
	int		z1;
	float	angle;
	int		position_x;
	int		position_y;
	int		flag_hook;
	int		signx;
	int		signy;
	int		deltay;
	int		deltax;
	int		error;
	int		error2;
}	t_data;

int		**map_create(char *book, t_data fdf);
int		map_height(char *book);
int		map_width(char *book);
void	drawrotation(t_data *fdf);
void	drawrotation_pic(t_data *fdf);
void	drawrotation_flag(int x, int y, int flag, t_data *fdf);
void	drawrotation_color_and_scale(t_data *fdf);
void	drawrotation_line(t_data *fdf, int color);
void	drawline(t_data *fdf);
void	angle(int *x, int *y, int z, t_data *fdf);
void	drawmap_color_and_scale(t_data *fdf);
void	drawmap_flag(int x, int y, int flag, t_data *fdf);
void	drawmap_pic(t_data *fdf);
void	movie_hook(int key, t_data *fdf);
int		key_hook(int key, t_data *fdf);
int		exit_hook(t_data *fdf);
void	drawmap(t_data *fdf);

#endif
