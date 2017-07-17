/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syoung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 07:12:58 by syoung            #+#    #+#             */
/*   Updated: 2017/07/17 07:13:01 by syoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_draw_init(t_draw *d)
{
	d->camerax = 2 * d->x / (double)(d->w) - 1;
	d->rayposx = d->posx;
	d->rayposy = d->posy;
	d->raydirx = d->dirx + d->planex * d->camerax;
	d->raydiry = d->diry + d->planey * d->camerax;
	d->mapx = (int)(d->rayposx);
	d->mapy = (int)(d->rayposy);
	d->deltadistx = sqrt(1 + (d->raydiry * d->raydiry) /
		(d->raydirx * d->raydirx));
	d->deltadisty = sqrt(1 + (d->raydirx * d->raydirx) /
		(d->raydiry * d->raydiry));
	d->hit = 0;
}

void	ft_color(t_draw *d)
{
	if (d->map[d->mapx][d->mapy] == 1)
		d->color = 0xe0ffff;
	else if (d->map[d->mapx][d->mapy] == 2)
		d->color = 0x8b;
	else if (d->map[d->mapx][d->mapy] == 3)
		d->color = 0x90ee90;
	else if (d->map[d->mapx][d->mapy] == 4)
		d->color = 0xfaebd7;
	else
		d->color = 0xffdab9;
	if (d->side == 1)
		d->color = d->color / 2;
}

void	ft_draw_rays(t_draw *d)
{
	int i;
	int g;

	i = 0;
	g = 0;
	d->k = d->drawstart;
	while (d->k <= d->drawend)
	{
		mlx_pixel_put(d->m.mlx, d->m.win, d->x, d->k, d->color);
		d->k++;
	}
	i = d->k;
	while (i < d->h)
	{
		mlx_pixel_put(d->m.mlx, d->m.win, d->x, i, 0xe5e5e5);
		i++;
	}
	g = d->drawstart;
	while (g > 0)
	{
		mlx_pixel_put(d->m.mlx, d->m.win, d->x, g, 0xa9a9a9);
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
		d.drawstart = -d.lineheight / 2 + d.h / 2;
		if (d.drawstart < 0)
			d.drawstart = 0;
		d.drawend = d.lineheight / 2 + d.h / 2;
		if (d.drawend >= d.h)
			d.drawend = d.h - 1;
		ft_color(&d);
		ft_draw_rays(&d);
		d.x++;
	}
}
