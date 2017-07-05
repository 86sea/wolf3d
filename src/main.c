
#include "wolf3d.h"
#include "../libft/libft.h"
# define mapWidth 24
# define mapHeight 24

void      line(t_mlx m, t_line n, int color)
{
  n.dx = ft_abs(n.x1 - n.x0);
  n.sx = n.x0 < n.x1 ? 1 : -1;
  n.dy = ft_abs(n.y1 - n.y0);
  n.sy = n.y0 < n.y1 ? 1 : -1;
  n.err = (n.dx > n.dy ? n.dx : -n.dy) / 2;
  while (1)
  {
    if (n.x0 == n.x1 && n.y0 == n.y1)
      break ;
    n.e2 = n.err;
    if (n.e2 > -n.dx)
    {
      n.err -= n.dy;
      n.x0 += n.sx;
    }
    if (n.e2 < n.dy)
    {
      n.err += n.dx;
      n.y0 += n.sy;
    }
   // rotate(m, n.x0, n.y0, color);
    mlx_pixel_put(m.mlx, m.win, n.x1, n.y1, color);
  }
}

s_inter find_h_hit(int ray, t_player p, int map[][])
{
	int h;
	s_inter A;
	int Xa;
	int Ya;

	h = 0
	if (ray > 0 && ray < 180)
	{
		A.y = ((p.y / 64) * 64) - 1;
		Ya = 64;
	}
	else
	{
		A.y = ((p.y / 64) * 64) + 64;
		Ya = -64;
	}
	Xa = 64/tan(ray);
	A.x = p.x + (p.y - A.y) / tan(ray);
	while (h == 0)
	{
		
		if (map[A.x >> 8][A.y >> 8] != 0)
		{
			hit = 1;
			break ;
		}
		A.x += Xa;
		A.y += Ya;
	}
	return (A);
}

s_inter find_v_hit(int ray, t_player p, int map[][])
{
	int h;
	s_inter A;
	int Xa;
	int Ya;

	h = 0;
	if (ray < 90 || ray > 270)
	{
		A.x = ((p.x / 64) * 64) + 64
		Xa = 64;
	}
	else
	{
		A.x = ((p.x / 64) * 64) - 1;
		Xa = -64;
	}
	Ya = 64 * tan(ray);
	A.y = Py + (p.x - A.x) * tan(ray);
	while (h == 0)
	{
		if (map[A.x >> 8][A.y >> 8] != 0)
		{
			hit = 1;
			break ;
		}
		A.x += Xa;
		A.y += Ya;
	}
	return (A);
}

int		main(void)
{
	t_mlx m;
	t_player p;
	int planedst;
	int rayangle;
	int map[MAPW][MAPH] =
	{1, 1, 1, 1, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 1, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 1, 1, 1, 1};
	s_inter		hh;
	s_inter		hv;
	int ray;

	p.x = 64 * 2 - 32;
	p.y = 64 * 5 - 32;
	p.view = 90;
	m.mlx = mlx_init();
	m.win = mlx_create_window(m.mlx WINHEIGHT, WINWIDTH, "wolf3D")
  	planedst = (WINDITH / tan(FOV/2));
	rayangle = WIDTH / FOV;
	ray = p.view - (FOV / 2);
	int Ya;
	int Xa;
	while (ray < (FOV / 2 + p.view))
	{
		hh = find_h_hit(ray, p, map);
		hv = find_v_hit(ray, p, map);
	}
	ray += rayangel;	
	mlx_loop(m.mlx);

	return (0);
}
