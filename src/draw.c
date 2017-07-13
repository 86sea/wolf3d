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

t_draw	ft_draw_init(t_draw *d)
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
t_draw	ft_side_dst(t_draw *d)
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
void	ft_draw(t_draw d)
{

	while (d.x < d.w)
	{
	ft_draw_init(&d);
		//calculate step and initial sideDist
		//d = ft_side_dst(d);
	ft_side_dst(&d);
	      //perform DDA
		while (d.hit == 0)
		{
			//jump to next map square, OR in d.x-direction, OR in y-direction
			if (d.sideDistX < d.sideDistY)
			{
				d.sideDistX += d.deltaDistX;
				d.mapX += d.stepX;
				d.side = 0;
			}
			else
			{
				d.sideDistY += d.deltaDistY;
				d.mapY += d.stepY;
				d.side = 1;
			}
	        //Check if ray has d.hit a wall
			if (worldMap[d.mapX][d.mapY] > 0) d.hit = 1;
		}
		//Calculate distance projected on camera direction (oblique distance will give fisheye effect!)
		if (d.side == 0)
			d.perpWallDist = (d.mapX - d.rayPosX + (1 - d.stepX) / 2) / d.rayDirX;
		else
			d.perpWallDist = (d.mapY - d.rayPosY + (1 - d.stepY) / 2) / d.rayDirY;
		d.lineHeight = (int)(d.h / d.perpWallDist);
		//calculate lowest and highest pixel to fill in current stripe
		d.drawStart = -d.lineHeight / 2 + d.h / 2;
		if (d.drawStart < 0)
			d.drawStart = 0;
			d.drawEnd = d.lineHeight / 2 + d.h / 2;
		if (d.drawEnd >= d.h)
			d.drawEnd = d.h - 1;
	//choose wall d.color
		if (worldMap[d.mapX][d.mapY] == 1)
			d.color = 0x00FF0000; //red
		else if (worldMap[d.mapX][d.mapY] == 2)
			d.color = 0x0000FF00; //green
		else if (worldMap[d.mapX][d.mapY] == 3)
			d.color = 0x000000FF; //blue 
		else if (worldMap[d.mapX][d.mapY] == 4)
			d.color = 0x00FFFFFF; //white
		else
			d.color = 0x00FFFF00; //yellow
		//give d.x and y sides different brightness
		if (d.side == 1)
			d.color = d.color / 2;
		//draw the pixels of the stripe as a vertical line
		d.k = d.drawStart;
		while (d.k <= d.drawEnd)
		{
			mlx_pixel_put(d.m.mlx, d.m.win, d.x, d.k, d.color);
			d.k++;
		}
		int i;
		i = d.k;
		while ( i < d.h)
		{
			mlx_pixel_put(d.m.mlx, d.m.win, d.x, i, 0x00AAAAAA);
			i++;
		}
		int g;
		g = d.drawStart;
		while (g > 0)
		{
			mlx_pixel_put(d.m.mlx, d.m.win, d.x, g, 0x00555555);
			g--;
		}
		d.x++;
	}
}