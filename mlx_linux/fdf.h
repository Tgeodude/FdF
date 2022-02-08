#ifndef FDF_H
# define FDF_H
# include <mlx.h>
# include <fcntl.h>
# include "get_next_line.h"
# include "libft/libft.h"

typedef struct s_data {
	int width;
	int height;
} t_data;

int	**map_create(int fd);
int	map_height(int fd);
int	map_width(int fd);

#endif
