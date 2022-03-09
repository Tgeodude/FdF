#include "fdf.h"

int	key_hook(int key, t_data *fdf)
{
	if (key == 53)
	{
		mlx_destroy_window(fdf->mlx_p, fdf->mlx_w);
		exit(0);
	}
	return (0);
}