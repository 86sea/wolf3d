#include "mlx.h"
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

int		line_dst(t_player p, t_inter B, int ray)
{
	int dst;

	dst = ft_abs(p.x - B.x) / cos(ray); //distorted
	dst *= cos(ray - p.view);			//fixed dist
	return (dst);
}

t_inter find_h_hit(int ray, t_player p, int **map)
{
	int h;
	t_inter A;
	int Xa;
	int Ya;

	h = 0;
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
			h = 1;
			break ;
		}
		A.x += Xa;
		A.y += Ya;
	}
	return (A);
}

t_inter find_v_hit(int ray, t_player p, int **map)
{
	int h;
	t_inter A;
	int Xa;
	int Ya;

	h = 0;
	if (ray < 90 || ray > 270)
	{
		A.x = ((p.x / 64) * 64) + 64;
		Xa = 64;
	}
	else
	{
		A.x = ((p.x / 64) * 64) - 1;
		Xa = -64;
	}
	Ya = 64 * tan(ray);
	A.y = p.y + (p.x - A.x) * tan(ray);
	while (h == 0)
	{
		if (map[A.x >> 8][A.y >> 8] != 0)
		{
			h = 1;
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
	{
	{1, 1, 1, 1, 1},
	{1, 0, 0, 0, 1},
	{1, 0, 1, 0, 1},
	{1, 0, 0, 0, 1},
	{1, 1, 1, 1, 1}
	};
	t_inter		hh;
	t_inter		hv;
	t_inter		wall;
	t_line		slice;
	int ray;
	int Ya;
	int Xa;
	int dh;
	int dv;
	int slice_height;
	int slice_width;
	int k;
	int color;
	int walldst;

	p.x = 64 * 2 - 32;
	p.y = 64 * 5 - 32;
	p.view = 90;
	m.mlx = mlx_init();
	m.win = mlx_new_window(m.mlx, WINHEIGHT, WINWIDTH, "wolf3D");
  	planedst = (WINWIDTH / tan(FOV/2));
	rayangle = WINWIDTH / FOV;
	ray = p.view - (FOV / 2);


	color = 0x00FFFFFF;
	slice_width	= rayangle;

	slice_height = GRIDH;
	while (ray < (FOV / 2 + p.view))
	{
		slice.x0 = 1; 			//collumn
		slice.x1 = slice.x0;
		hh = find_h_hit(ray, p, map);
		hv = find_v_hit(ray, p, map);
		dh = line_dst(p, hh, ray);
		dv = line_dst(p, hv, ray);
		if (dh < dv)
		{
			wall = hh;
			walldst = dh;
		}
		else
		{
			wall = hv;
			walldst = dv;
		}
		slice_height = slice_height/walldst * planedst;
		slice.y0 = (WINHEIGHT / 2) - (slice_height / 2); //slice_start
		slice.y1 = slice.x0 + slice_height;
		k  = 0;
		while (k < slice_width)
		{
			line(m, slice, color);
			slice.x0++;
			k++;
		}
	}
	ray += rayangle;	
	mlx_loop(m.mlx);

	return (0);
}
