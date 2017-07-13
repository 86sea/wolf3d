/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syoung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 07:02:57 by syoung            #+#    #+#             */
/*   Updated: 2017/07/10 07:03:00 by syoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

	int worldMap[mapHeight][mapWidth]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,1,2,3,4,0,0,1,0,1,1,1,1,1,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	ft_draw_init(t_draw *d)
{
	d->cameraX = 2 * d->x / (double)(d->w) - 1; 
	d->rayPosX = d->posX;
	d->rayPosY = d->posY;
	d->rayDirX = d->dirX + d->planeX * d->cameraX;
	d->rayDirY = d->dirY + d->planeY * d->cameraX;
	d->mapX = (int)(d->rayPosX);
	d->mapY = (int)(d->rayPosY);
	d->deltaDistX = sqrt(1 + (d->rayDirY * d->rayDirY) / (d->rayDirX * d->rayDirX));
	d->deltaDistY = sqrt(1 + (d->rayDirX * d->rayDirX) / (d->rayDirY * d->rayDirY));
	d->hit = 0;
}

void	ft_color(t_draw *d)
{
	if (worldMap[d->mapX][d->mapY] == 1)
		d->color = 0x00FF0000;
	else if (worldMap[d->mapX][d->mapY] == 2)
		d->color = 0x0000FF00;
	else if (worldMap[d->mapX][d->mapY] == 3)
		d->color = 0x000000FF;
	else if (worldMap[d->mapX][d->mapY] == 4)
		d->color = 0x00FFFFFF;
	else
		d->color = 0x00FFFF00;
	if (d->side == 1)
		d->color = d->color / 2;
}

void	ft_draw_rays(t_draw *d)
{
	int i;
	int g;

	d->k = d->drawStart;
	while (d->k <= d->drawEnd)
	{
		mlx_pixel_put(d->m.mlx, d->m.win, d->x, d->k, d->color);
		d->k++;
	}
	i = d->k;
	while ( i < d->h)
	{
		mlx_pixel_put(d->m.mlx, d->m.win, d->x, i, 0x00AAAAAA);
		i++;
	}
		g = d->drawStart;
		while (g > 0)
		{
			mlx_pixel_put(d->m.mlx, d->m.win, d->x, g, 0x00555555);
			g--;
		}
}

void	ft_draw(t_draw d)
{
	while (d.x < d.w)
	{

		ft_draw_init(&d);
		ft_side_dst(&d);
		ft_dda(&d);
		ft_dist_corr(&d);
		//calculate lowest and highest pixel to fill in current stripe
		d.drawStart = -d.lineHeight / 2 + d.h / 2;
		if (d.drawStart < 0)
			d.drawStart = 0;
			d.drawEnd = d.lineHeight / 2 + d.h / 2;
		if (d.drawEnd >= d.h)
			d.drawEnd = d.h - 1;
		ft_color(&d);
		ft_draw_rays(&d);
		d.x++;
	}
}