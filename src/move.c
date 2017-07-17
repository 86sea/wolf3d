/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syoung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 07:03:12 by syoung            #+#    #+#             */
/*   Updated: 2017/07/17 07:03:15 by syoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	move_foward(t_main *temp)
{
	if (temp->d.map[(int)(temp->d.posx + temp->d.dirx
		* MOVE_SPEED)][(int)(temp->d.posy)] == 0)
		temp->d.posx += temp->d.dirx * MOVE_SPEED;
	if (temp->d.map[(int)(temp->d.posx)][(int)(temp->d.posy
		+ temp->d.diry * MOVE_SPEED)] == 0)
		temp->d.posy += temp->d.diry * MOVE_SPEED;
}

void	move_backward(t_main *temp)
{
	if (temp->d.map[(int)(temp->d.posx + temp->d.dirx
		* MOVE_SPEED)][(int)(temp->d.posy)] == 0)
		temp->d.posx += temp->d.dirx * MOVE_SPEED;
	if (temp->d.map[(int)(temp->d.posx)][(int)(temp->d.posy
		+ temp->d.diry * MOVE_SPEED)] == 0)
		temp->d.posy += temp->d.diry * MOVE_SPEED;
}

void	turn_right(t_main *temp)
{
	double old_dirx;
	double old_planex;

	old_dirx = temp->d.dirx;
	temp->d.dirx = temp->d.dirx * cos(-TURN_SPEED)
	- temp->d.diry * sin(-TURN_SPEED);
	temp->d.diry = old_dirx * sin(-TURN_SPEED)
	+ temp->d.diry * cos(-TURN_SPEED);
	old_planex = temp->d.planex;
	temp->d.planex = temp->d.planex * cos(-TURN_SPEED)
	- temp->d.planey * sin(-TURN_SPEED);
	temp->d.planey = old_planex * sin(-TURN_SPEED)
	+ temp->d.planey * cos(-TURN_SPEED);
}

void	turn_left(t_main *temp)
{
	double old_dirx;
	double old_planex;

	old_dirx = temp->d.dirx;
	temp->d.dirx = temp->d.dirx * cos(TURN_SPEED)
	- temp->d.diry * sin(TURN_SPEED);
	temp->d.diry = old_dirx * sin(TURN_SPEED)
	+ temp->d.diry * cos(TURN_SPEED);
	old_planex = temp->d.planex;
	temp->d.planex = temp->d.planex * cos(TURN_SPEED)
	- temp->d.planey * sin(TURN_SPEED);
	temp->d.planey = old_planex * sin(TURN_SPEED)
	+ temp->d.planey * cos(TURN_SPEED);
}
