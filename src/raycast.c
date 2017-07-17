/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syoung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 07:11:16 by syoung            #+#    #+#             */
/*   Updated: 2017/07/17 07:11:17 by syoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ft_side_dst(t_draw *d)
{
	if (d->raydirx < 0)
	{
		d->stepx = -1;
		d->sidedistx = (d->rayposx - d->mapx) * d->deltadistx;
	}
	else
	{
		d->stepx = 1;
		d->sidedistx = (d->mapx + 1.0 - d->rayposx) * d->deltadistx;
	}
	if (d->raydiry < 0)
	{
		d->stepy = -1;
		d->sidedisty = (d->rayposy - d->mapy) * d->deltadisty;
	}
	else
	{
		d->stepy = 1;
		d->sidedisty = (d->mapy + 1.0 - d->rayposy) * d->deltadisty;
	}
}

void	ft_dda(t_draw *d)
{
	while (d->hit == 0)
	{
		if (d->sidedistx < d->sidedisty)
		{
			d->sidedistx += d->deltadistx;
			d->mapx += d->stepx;
			d->side = 0;
		}
		else
		{
			d->sidedisty += d->deltadisty;
			d->mapy += d->stepy;
			d->side = 1;
		}
		if (d->map[d->mapx][d->mapy] > 0)
			d->hit = 1;
	}
}

void	ft_dist_corr(t_draw *d)
{
	if (d->side == 0)
		d->perpwalldist = (d->mapx - d->rayposx
			+ (1 - d->stepx) / 2) / d->raydirx;
	else
		d->perpwalldist = (d->mapy - d->rayposy
			+ (1 - d->stepy) / 2) / d->raydiry;
	d->lineheight = (int)(d->h / d->perpwalldist);
}
