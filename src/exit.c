#include "wolf3d.h"

void ft_exit(t_main *temp)
{
	int i;
	int *p;

	p = NULL;
	i = 0;
	while (i < mapWidth)
	{
		p = temp->d.map[i];
		free(p);
		i++;
	}
	//free(temp->d.map[i]);
	mlx_destroy_window(temp->d.m.mlx, temp->d.m.win);
	exit(0);
}