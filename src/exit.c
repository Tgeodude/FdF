#include "fdf.h"

int	exit_hook(t_data *fdf)
{
	mlx_destroy_window(fdf->mlx_p, fdf->mlx_w);
	exit(0);
}