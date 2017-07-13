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

int		keypress(int keycode, void *d)
{
int worldMap[mapHeight][mapWidth] =
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,1,2,3,4,0,0,1,0,1,1,1,1,1,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
	t_main *temp;

	temp = (t_main *)d;
	ft_putnbr(keycode);
	ft_putchar('\n');
	if (keycode == 65307)
	{
		ft_exit(temp);
	}
	if (keycode == FOWARD)
		move_foward(temp, worldMap);
	if (keycode == BACKWARD)
		move_backward(temp, worldMap);
	if (keycode == LOOK_RIGHT)
		turn_right(temp, worldMap);
	if (keycode == 97)
		turn_left(temp, worldMap);
	mlx_clear_window(temp->d.m.mlx, temp->d.m.win);
	ft_draw(temp->d);
	return (0);
}

void	ft_init_map(t_draw *d)
{}
t_draw	ft_init(t_draw d)
{	

	ft_read("map.txt", &d);
	d.posX = 2;
	d.posY = 2;  //d.x and y start position
	d.dirX = -1,
	d.dirY = 0;
	d.planeX = 0;
	d.planeY = 0.66; 
	d.x = 0;
	d.h = 512;
	d.w = 384;
	d.m.mlx = mlx_init();
	d.m.win = mlx_new_window(d.m.mlx, 384, 512, "Raycaster");
	return (d);
}
int		main(void)
{
	t_main d;

	d.d = ft_init(d.d);
	ft_draw(d.d);
	mlx_key_hook(d.d.m.win, keypress, &d);
	mlx_loop(d.d.m.mlx);
	return (0);
}

