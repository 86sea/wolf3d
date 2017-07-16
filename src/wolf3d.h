#ifndef  WOLF3D_H
# define WOLF3D_H
# include <math.h>
# include <string.h>
# include "mlx.h"
# include "../libft/libft.h"
# include "../libft/get_next_line.h"
# include <math.h>
# include <unistd.h>
#include <fcntl.h>
# include <stdlib.h>
# define mapWidth 24
# define mapHeight 5
# define FOWARD 119
# define BACKWARD 115
# define LOOK_LEFT 97
# define LOOK_RIGHT 100
# define ESC 65307
# define MOVE_SPEED 0.5
# define TURN_SPEED 0.5


typedef struct	s_mlx
{
	void		*mlx;
	void		*win;
}				t_mlx;
typedef struct s_draw
{
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
	double		cameraX;
	double		rayPosX;
	double		rayPosY;
	double		rayDirX;
	double		rayDirY;
	double		sideDistX;
	double		sideDistY;
	double		deltaDistX;
	double		deltaDistY;
	double		perpWallDist;
	int			h;
	int			w;
	int			x;
	int			stepX;
	int			stepY;
	int			hit;
	int			side;
	int			lineHeight;
	int			drawStart;
	int			drawEnd;
	int			k;
	int			mapX;
	int			mapY;
	int			color;
	t_mlx		m;
	int			**map;
}				t_draw;
typedef struct s_main
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
int		keypress(int keycode, void *m);
void	ft_draw(t_draw d);
void	move_foward(t_main *temp);
void	move_backward(t_main *temp);
void	turn_right(t_main *temp);
void	turn_left(t_main *temp);
void	ft_draw_init(t_draw *d);
void	ft_side_dst(t_draw *d);
void	ft_dda(t_draw *d);
void	ft_dist_corr(t_draw *d);
void	ft_color(t_draw *d);
void	ft_read(char *file, t_draw *d);
void	ft_init(t_draw *d);
void 	ft_exit(t_draw *d);
int		expose(void *d);
#endif
