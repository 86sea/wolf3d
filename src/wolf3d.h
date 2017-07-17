/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syoung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 07:14:03 by syoung            #+#    #+#             */
/*   Updated: 2017/07/17 07:14:05 by syoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include <math.h>
# include <string.h>
# include "mlx.h"
# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# define FOWARD 13
# define BACKWARD 1
# define LOOK_LEFT 0
# define LOOK_RIGHT 2
# define ESC 53
# define MOVE_SPEED 0.5
# define TURN_SPEED 0.5
# define WIN_HEIGHT 150
# define WIN_WIDTH 150

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
}				t_mlx;
typedef struct	s_draw
{
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	double		camerax;
	double		rayposx;
	double		rayposy;
	double		raydirx;
	double		raydiry;
	double		sidedistx;
	double		sidedisty;
	double		deltadistx;
	double		deltadisty;
	double		perpwalldist;
	int			h;
	int			w;
	int			x;
	int			stepx;
	int			stepy;
	int			hit;
	int			side;
	int			lineheight;
	int			drawstart;
	int			drawend;
	int			k;
	int			mapx;
	int			mapy;
	int			color;
	t_mlx		m;
	int			**map;
}				t_draw;
typedef struct	s_main
{
	t_draw d;
}				t_main;
typedef	struct	s_read
{
	int			col_count;
	int			row_count;
	char		*row;
	char		**split;
	int			fd;
	int			i;
	int			j;
}				t_read;
int				keypress(int keycode, void *m);
void			ft_draw(t_draw d);
void			move_foward(t_main *temp);
void			move_backward(t_main *temp);
void			turn_right(t_main *temp);
void			turn_left(t_main *temp);
void			ft_draw_init(t_draw *d);
void			ft_side_dst(t_draw *d);
void			ft_dda(t_draw *d);
void			ft_dist_corr(t_draw *d);
void			ft_color(t_draw *d);
void			ft_read(char *file, t_draw *d);
void			ft_init(t_draw *d);
void			ft_exit(t_draw *d);
int				expose(void *d);
#endif
