#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include "get_next_line.h"
# include "libft/libft.h"
# include <unistd.h>
# include <stdlib.h>

typedef struct s_data {
	int	width;
	int	height;
	int	**map;
} t_data;

int	**map_create(char *maps);
int	map_height(char *maps);
int	map_width(char *maps);

#endif
