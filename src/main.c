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

int		keypress(int keycode, void *d)
{
	t_main *temp;
int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
	temp = (t_main *)d;
	double oldDirX;
	double oldPlaneX;
	double rotSpeed = 2.0;
	double moveSpeed = 2.0;
	ft_putnbr(keycode);
	ft_putchar('\n');
	if (keycode == 53)
	{
		mlx_destroy_window(temp->d.m.mlx, temp->d.m.win);
		exit(0);
	}
	if (keycode == 13)
	{
		if (worldMap[(int)(temp->d.posX + temp->d.dirX * moveSpeed)][(int)(temp->d.posY)] == 0)
			temp->d.posX += temp->d.dirX * moveSpeed;
		if (worldMap[(int)(temp->d.posX)][(int)(temp->d.posY + temp->d.dirY * moveSpeed)] == 0)
			temp->d.posY += temp->d.dirY * moveSpeed;
	}
	if (keycode == 1)
	{
		if (worldMap[(int)(temp->d.posX - temp->d.dirX * moveSpeed)][(int)(temp->d.posY)] == 0) 
		temp->d.posX -= temp->d.dirX * moveSpeed;
		if (worldMap[(int)(temp->d.posX)][(int)(temp->d.posY - temp->d.dirY * moveSpeed)] == 0) 
		temp->d.posY -= temp->d.dirY * moveSpeed;
	}
    //rotate to the right
    if (keycode == 2)
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
	if (keycode == 0)
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
	d.posX = 22;
	d.posY = 12;  //d.x and y start position
	d.dirX = -1,
	d.dirY = 0;
	d.planeX = 0;
	d.planeY = 0.66; 
	d.x = 0;
	d.h = 512;
	d.w = 384;
	d.m.mlx = mlx_init();
	d.m.win = mlx_new_window(d.m.mlx, 512, 384, "Raycaster");
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

