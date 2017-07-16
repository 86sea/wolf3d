#include "wolf3d.h"

void	ft_side_dst(t_draw *d)
{
	if (d->rayDirX < 0)
	{
		d->stepX = -1;
		d->sideDistX = (d->rayPosX - d->mapX) * d->deltaDistX;
	}
	else
	{
		d->stepX = 1;
		d->sideDistX = (d->mapX + 1.0 - d->rayPosX) * d->deltaDistX;
	}
	if (d->rayDirY < 0)
	{
		d->stepY = -1;
		d->sideDistY = (d->rayPosY - d->mapY) * d->deltaDistY;
	}
	else
	{
		d->stepY = 1;
		d->sideDistY = (d->mapY + 1.0 - d->rayPosY) * d->deltaDistY;
	}
}

void	ft_dda(t_draw *d)
{
	while (d->hit == 0)
	{
		if (d->sideDistX < d->sideDistY)
		{
			d->sideDistX += d->deltaDistX;
			d->mapX += d->stepX;
			d->side = 0;
		}
		else
		{
			d->sideDistY += d->deltaDistY;
			d->mapY += d->stepY;
			d->side = 1;
		}
		if (d->map[d->mapX][d->mapY] > 0)
			d->hit = 1;
	}
}

void	ft_dist_corr(t_draw *d)
{
	if (d->side == 0)
		d->perpWallDist = (d->mapX - d->rayPosX + (1 - d->stepX) / 2) / d->rayDirX;
	else
		d->perpWallDist = (d->mapY - d->rayPosY + (1 - d->stepY) / 2) / d->rayDirY;
	d->lineHeight = (int)(d->h / d->perpWallDist);
}