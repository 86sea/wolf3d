/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syoung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/10 07:03:13 by syoung            #+#    #+#             */
/*   Updated: 2017/07/10 07:03:19 by syoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include "../libft/libft.h"
#include <stdio.h>

int			keypress(int keycode, void *d)
{
	t_main *temp;

	temp = (t_main *)d;
	if (keycode == ESC)
		ft_exit(&temp->d);
	if (keycode == FOWARD)
		move_foward(temp);
	if (keycode == BACKWARD)
		move_backward(temp);
	if (keycode == LOOK_RIGHT)
		turn_right(temp);
	if (keycode == LOOK_LEFT)
		turn_left(temp);
	mlx_clear_window(temp->d.m.mlx, temp->d.m.win);
	ft_draw(temp->d);
	return (keycode);
}

int			expose(void *d)
{
	t_main *temp;

	temp = (t_main *)d;
	mlx_clear_window(temp->d.m.mlx, temp->d.m.win);
	ft_draw(temp->d);
	return (1);
}

void		ft_init(t_draw *d)
{
	d->posx = 5;
	d->posy = 5;
	d->dirx = -1;
	d->diry = 0;
	d->planex = 0;
	d->planey = 0.66;
	d->x = 0;
	d->h = WIN_HEIGHT;
	d->w = WIN_WIDTH;
	d->m.mlx = mlx_init();
	d->m.win = mlx_new_window(d->m.mlx, WIN_WIDTH, WIN_HEIGHT, "Raycaster");
}

int			main(void)
{
	t_main d;

	ft_init(&d.d);
	ft_read("map.txt", &d.d);
	mlx_expose_hook(d.d.m.win, expose, &d.d);
	mlx_key_hook(d.d.m.win, keypress, &d);
	mlx_loop(d.d.m.mlx);
	return (0);
}
