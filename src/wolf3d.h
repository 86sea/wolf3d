#ifndef  WOLF3D_H
# define WOLF3D_H
# include <math.h>
# include <string.h>
# include "mlx.h"
# include <stdio.h>
# include "../libft/libft.h"
# include <math.h>
# define mapWidth 24
# define mapHeight 5

typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
}				t_mlx;
typedef struct s_draw
{
	double		posX;
	double		posY; //x and y start position
	double			dirX;
	double		dirY; //initial direction vector
	double		planeX;
	double		planeY;
	double		cameraX;
	double		rayPosX;
	double		rayPosY;
	double		rayDirX;
	double		rayDirY; //the 2d raycaster version of camera plane
	double		sideDistX;  //length of ray from current position to next x or y-side
	double		sideDistY;
	double		deltaDistX; //length of ray from one x or y-side to next x or y-side
	double		deltaDistY;
	double		perpWallDist;
	int			h;
	int			w;
	int			x;
	int			stepX; //what direction to step in x or y-direction (either +1 or -1)
	int			stepY;
	int			hit;  //was there a wall hit?
	int			side; //was a NS or a EW wall hit?
	int			lineHeight;       //Calculate height of line to draw on screen
	int			drawStart;
	int			drawEnd;
	int			k;
	int			mapX;			//which box of the map we're in
	int			mapY;
	int			color;
	t_mlx		m;
	void		*img;
	char		*frame;
}				t_draw;
typedef struct s_main
{
	t_draw d;
}				t_main;
int		keypress(int keycode, void *m);
void	ft_draw(t_draw d);

#endif
