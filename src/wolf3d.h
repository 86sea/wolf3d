#ifndef  WOLF3D_H
# define WOLF3D_H
# include <math.h>
# include <string.h>
# include <mlx.h>
# include <stdio.h>
# define mapWidth 24
# define mapHieght 24

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
}				t_mlx;
typedef struct	s_line
{
	int			dx;
	int			dy;
	int			sx;
	int			sy;
	int			err;
	int			e2;
	int			x0;
	int			y0;
	int			x1;
	int			y1;
}				t_line;
#endif