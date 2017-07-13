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
void	test(void)
{
	printf("test\n");
}
int		keypress(int keycode, void *d)
{
const int worldMap[mapHeight][mapWidth]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,1,2,3,4,0,0,1,0,1,1,1,1,1,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
	t_main *temp;
	ft_putnbr(keycode);
	test();

	temp = (t_main *)d;
	double 8+976=`;
	double oldPlaneX;
	double rotSpeed = 0.5;
	double moveSpeed = 0.5;
	ft_putnbr(keycode);
	ft_putchar('\n');
	if (keycode == 65307)
	{
		mlx_destroy_window(temp->d.m.mlx, temp->d.m.win);
		exit(0);
	}
	if (keycode == 119)
	{
		if (worldMap[(int)(temp->d.posX + temp->d.dirX * moveSpeed)][(int)(temp->d.posY)] == 0)
			temp->d.posX += temp->d.dirX * moveSpeed;
		if (worldMap[(int)(temp->d.posX)][(int)(temp->d.posY + temp->d.dirY * moveSpeed)] == 0)
			temp->d.posY += temp->d.dirY * moveSpeed;
	}
	if (keycode == 115)
	{
		if (worldMap[(int)(temp->d.posX - temp->d.dirX * moveSpeed)][(int)(temp->d.posY)] == 0) 
		temp->d.posX -= temp->d.dirX * moveSpeed;
		if (worldMap[(int)(temp->d.posX)][(int)(temp->d.posY - temp->d.dirY * moveSpeed)] == 0) 
		temp->d.posY -= temp->d.dirY * moveSpeed;
	}
    //rotate to the right
    if (keycode == 100)
    {
      //both camera direction and camera plane must be rotated
      oldDirX = temp->d.dirX;
      temp->d.dirX = temp->d.dirX * cos(-rotSpeed) - temp->d.dirY * sin(-rotSpeed);
      temp->d.dirY = oldDirX * sin(-rotSpeed) + temp->d.dirY * cos(-rotSpeed);
      oldPlaneX = temp->d.planeX;
      temp->d.planeX = temp->d.planeX * cos(-rotSpeed) - temp->d.planeY * sin(-rotSpeed);
      temp->d.planeY = oldPlaneX * sin(-rotSpeed) + temp->d.planeY * cos(-rotSpeed);
    }
    //rotate to the left
	if (keycode == 97)
	{
      //both camera direction and camera plane must be rotated
		oldDirX = temp->d.dirX;
		temp->d.dirX = temp->d.dirX * cos(rotSpeed) - temp->d.dirY * sin(rotSpeed);
		temp->d.dirY = oldDirX * sin(rotSpeed) + temp->d.dirY * cos(rotSpeed);
		oldPlaneX = temp->d.planeX;
		temp->d.planeX = temp->d.planeX * cos(rotSpeed) - temp->d.planeY * sin(rotSpeed);
		temp->d.planeY = oldPlaneX * sin(rotSpeed) + temp->d.planeY * cos(rotSpeed);
	}
	mlx_clear_window(temp->d.m.mlx, temp->d.m.win);
	ft_draw(temp->d);
	return (keycode);
}

t_draw ft_init(t_draw d)
{
	int endian;
	int bits;
	int size_line;

	size_line = 384;
	bits = 32;
	endian = 1;
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
	d.img = mlx_new_image(d.m.mlx, 384, 512);
	d.frame = mlx_get_data_addr(d.img, &bits, &size_line, &endian);
	return (d);
}
int main(void)
{
	t_main d;

	d.d = ft_init(d.d);
	ft_draw(d.d);
	mlx_key_hook(d.d.m.win, keypress, &d);
	mlx_loop(d.d.m.mlx);
	return (0);
}

