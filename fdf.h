#ifndef FDF_H
# define FDF_H
# include <mlx.h>
# include <fcntl.h>
# include "get_next_line.h"
# include "libft/libft.h"
# include "mlx.h"
# include "math.h"

typedef struct s_data {
	int width;
	int height;
	int	**map;
	void	*mlx_pointer;
	void	*mlx_window;
	int	scale;
	int	color;
	int	x1;
	int	x2;
	int	y1;
	int	y2;
	int	z;
	int	z1;
	float	angle;
	int	position_x;
	int	position_y;
	int	flag_hook;
	int	signX;
	int	signY;
	int	deltaY;
	int	deltaX;
	int	error;
	int	error2;
	int	flag_color;
	int	clr;
	int	step;
	int	step_cl;
} t_data;

int	**map_create(char *book, t_data fdf);
int	map_height(char *book);
int	map_width(char *book);
void	drawRotation(t_data *fdf);
void	drawRotation_pic(t_data *fdf);
void	drawRotation_flag(int x, int y, int flag, t_data *fdf);
void	drawRotation_color_and_scale(t_data *fdf);
void 	drawRotation_Line(t_data *fdf, int color);
void 	drawLine(t_data *fdf);
void	angle(int *x, int *y, int z, t_data *fdf);
void	drawMap_color_and_scale(t_data *fdf);
void	drawMap_flag(int x, int y, int flag, t_data *fdf);
void	drawMap_pic(t_data *fdf);
int	ft_color(t_data *fdf);
char	*get_me_color(int g);
char	calcul_hex(int val, char chr);

#endif
