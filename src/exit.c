#include "wolf3d.h"

void ft_exit(t_draw *d)
{
	/*int i;

	i = 0;
	while (i < mapHeight)
	{
		free(d->map[i]);
		i++;
	}
	free(d->map);*/
	mlx_destroy_window(d->m.mlx, d->m.win);
	exit(0);
}