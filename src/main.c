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
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};
int		keypress(int keycode, void *m)
{
	t_mlx *temp;

	temp = (t_mlx *)m;
	ft_putnbr(keycode);
	ft_putchar('\n');
	if (keycode == 53)
	{
		mlx_destroy_window(temp->mlx, temp->win);
		exit(0);
	}
	return (keycode);
}

void ft_draw()
{

}

int main(void)
{
	double posX = 22, posY = 12;  //x and y start position
	double dirX = -1, dirY = 0; //initial direction vector
	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
	t_mlx m;
 	t_line n;
//  double time = 0; //time of current frame
  //double oldTime = 0; //time of previous frame
	m.mlx = mlx_init();
	m.win = mlx_new_window(m.mlx, 512, 384, "Raycaster");
    int h = 512;
    int w = 384;
    int x;
	double cameraX;
	double rayPosX;
	double rayPosY;
	double rayDirX;
	double rayDirY;
	int mapX;			//which box of the map we're in
	int mapY;
	double sideDistX;  //length of ray from current position to next x or y-side
	double sideDistY;
	double deltaDistX; //length of ray from one x or y-side to next x or y-side
	double deltaDistY;
	double perpWallDist;
	int stepX; //what direction to step in x or y-direction (either +1 or -1)
	int stepY;
	int hit;  //was there a wall hit?
	int side; //was a NS or a EW wall hit?
	int lineHeight;       //Calculate height of line to draw on screen
	int drawStart;
	int drawEnd;
	int k;

	x = 0;
 // while(1)
  //{
    while (x < w)
    {
      //calculate ray position and direction
	cameraX = 2 * x / (double)(w) - 1; //x-coordinate in camera space
	rayPosX = posX;
	rayPosY = posY;
	rayDirX = dirX + planeX * cameraX;
	rayDirY = dirY + planeY * cameraX;
	      
	mapX = (int)(rayPosX);
	mapY = (int)(rayPosY);
	deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
	deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
	hit = 0; 
      //calculate step and initial sideDist
      if (rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (rayPosX - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - rayPosX) * deltaDistX;
      }
      if (rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (rayPosY - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - rayPosY) * deltaDistY;
      }
      //perform DDA
      while (hit == 0)
      {
        //jump to next map square, OR in x-direction, OR in y-direction
        if (sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        //Check if ray has hit a wall
        if (worldMap[mapX][mapY] > 0) hit = 1;
      }
      //Calculate distance projected on camera direction (oblique distance will give fisheye effect!)
      if (side == 0) perpWallDist = (mapX - rayPosX + (1 - stepX) / 2) / rayDirX;
      else           perpWallDist = (mapY - rayPosY + (1 - stepY) / 2) / rayDirY;
      lineHeight = (int)(h / perpWallDist);
      //calculate lowest and highest pixel to fill in current stripe
      drawStart = -lineHeight / 2 + h / 2;
      if(drawStart < 0)drawStart = 0;
      drawEnd = lineHeight / 2 + h / 2;
      if(drawEnd >= h)drawEnd = h - 1;

      //choose wall color
      int color;
      switch(worldMap[mapX][mapY])
      {
        case 1:  color = 0x00FF0000;  break; //red
        case 2:  color = 0x0000FF00;  break; //green
        case 3:  color = 0x000000FF;   break; //blue
        case 4:  color = 0x00FFFFFF;  break; //white
        default: color = 0x00FFFF00; break; //yellow
      }

      //give x and y sides different brightness
      if (side == 1) {color = color / 2;}

      //draw the pixels of the stripe as a vertical line
      n.x0 = x;
      n.x1 = x;
      n.y0 = drawEnd;
      n.y1 = drawStart;
      
      k = drawStart;
      while(k <= drawEnd)
      {
        mlx_pixel_put(m.mlx, m.win, x, k, color);
        k++;
      }
      x++;
    }
//  }
	mlx_key_hook(m.win, keypress, &m);
    mlx_loop(m.mlx);
}
    //timing for input and FPS counter
   /* oldTime = time;
    time = getTicks();
    double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
    print(1.0 / frameTime); //FPS counter
    redraw();
    cls(); */

    //speed modifiers
/*    double moveSpeed = 5.0; //the constant value is in squares/second
    double rotSpeed = 3.0; //the constant value is in radians/second
    readKeys();
    //move forward if no wall in front of you
    if (keyDown(SDLK_UP))
    {
      if(worldMap[int(posX + dirX * moveSpeed)][int(posY)] == false) posX += dirX * moveSpeed;
      if(worldMap[int(posX)][int(posY + dirY * moveSpeed)] == false) posY += dirY * moveSpeed;
    }
    //move backwards if no wall behind you
    if (keyDown(SDLK_DOWN))
    {
      if(worldMap[int(posX - dirX * moveSpeed)][int(posY)] == false) posX -= dirX * moveSpeed;
      if(worldMap[int(posX)][int(posY - dirY * moveSpeed)] == false) posY -= dirY * moveSpeed;
    }
    //rotate to the right
    if (keyDown(SDLK_RIGHT))
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = dirX;
      dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
      dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
      double oldPlaneX = planeX;
      planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
      planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
    }
    //rotate to the left
    if (keyDown(SDLK_LEFT))
    {
      //both camera direction and camera plane must be rotated
      double oldDirX = dirX;
      dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
      dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
      double oldPlaneX = planeX;
      planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
      planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
    } */
