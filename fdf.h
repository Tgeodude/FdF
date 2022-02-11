#ifndef FDF_H
# define FDF_H
# include <mlx.h>
# include <fcntl.h>
# include "get_next_line.h"
# include "libft/libft.h"
# include "mlx.h"

typedef struct s_data {
	int width;
	int height;
	int	**map;
	void	*mlx_pointer;
	void	*mlx_window;
	int	i_l;
	int	j_l;

} t_data;

int	**map_create(char *book, t_data fdf);
int	map_height(char *book);
int	map_width(char *book);

#endif
