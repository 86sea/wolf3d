#include "wolf3d.h"

void	move_foward(t_main *temp, int worldMap[mapHeight][mapWidth])
{
	if (worldMap[(int)(temp->d.posX + temp->d.dirX * MOVE_SPEED)][(int)(temp->d.posY)] == 0)
		temp->d.posX += temp->d.dirX * MOVE_SPEED;
	if (worldMap[(int)(temp->d.posX)][(int)(temp->d.posY + temp->d.dirY * MOVE_SPEED)] == 0)
		temp->d.posY += temp->d.dirY * MOVE_SPEED;
}

void	move_backward(t_main *temp, int worldMap[mapHeight][mapWidth])
{
	if (worldMap[(int)(temp->d.posX + temp->d.dirX * MOVE_SPEED)][(int)(temp->d.posY)] == 0)
		temp->d.posX += temp->d.dirX * MOVE_SPEED;
	if (worldMap[(int)(temp->d.posX)][(int)(temp->d.posY + temp->d.dirY * MOVE_SPEED)] == 0)
		temp->d.posY += temp->d.dirY * MOVE_SPEED;
}

void	turn_right(t_main *temp, int worldMap[mapHeight][mapWidth])
{
	double oldDirX;
	double oldPlaneX;
	
	oldDirX = temp->d.dirX;
	temp->d.dirX = temp->d.dirX * cos(-TURN_SPEED) - temp->d.dirY * sin(-TURN_SPEED);
	temp->d.dirY = oldDirX * sin(-TURN_SPEED) + temp->d.dirY * cos(-TURN_SPEED);
	oldPlaneX = temp->d.planeX;
	temp->d.planeX = temp->d.planeX * cos(-TURN_SPEED) - temp->d.planeY * sin(-TURN_SPEED);
	temp->d.planeY = oldPlaneX * sin(-TURN_SPEED) + temp->d.planeY * cos(-TURN_SPEED);
}
void	turn_left(t_main *temp, int worldMap[mapHeight][mapWidth])
{
	double oldDirX;
	double oldPlaneX;

	oldDirX = temp->d.dirX;
	temp->d.dirX = temp->d.dirX * cos(TURN_SPEED) - temp->d.dirY * sin(TURN_SPEED);
	temp->d.dirY = oldDirX * sin(TURN_SPEED) + temp->d.dirY * cos(TURN_SPEED);
	oldPlaneX = temp->d.planeX;
	temp->d.planeX = temp->d.planeX * cos(TURN_SPEED) - temp->d.planeY * sin(TURN_SPEED);
	temp->d.planeY = oldPlaneX * sin(TURN_SPEED) + temp->d.planeY * cos(TURN_SPEED);
}