#include "mlx.h"
#include "wolf3d.h"
#include "../libft/libft.h"


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
	int alpha;


		alpha = p.view - ray;
	dst = ft_abs(p.x - B.x) / cos(alpha); //distorted
	dst *= cos(alpha);			//fixed dist
	return (dst);
}

t_inter find_h_hit(int ray, t_player p, int map[][MAPH])
{
	int h;
	t_inter A;
	double Xa;
	double Ya;

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
	printf("# tan(ray) %f\n", tan(ray));
	Xa = 30;
	printf("tan 60 %f\n", tan(60));
	A.x = 100;//(p.x + (p.y - A.y) / (double)tan(ray));
	printf("p.x %d\n", p.x);
	printf("p.y %d\n", p.y);//tan(ray);
	printf("A.y %d\n", A.y);//tan(ray);
	printf("p.y - A.y %d\n", p.y - A.y);
	while (h == 0)
	{
		A.x = floor(A.x / 64);
		A.y = floor(A.y / 64);
		if (map[A.x][A.y] != 0)
		{
			h = 1;
			A.x = A.x * 64;
			A.y = A.y * 64;
			break ;
		}
		A.x = A.x * 64;
		A.y = A.y * 64;
		A.x += Xa;
		A.y += Ya;
	}
	return (A);
}

t_inter find_v_hit(int ray, t_player p, int map[][MAPH])
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
			//	printf("A.x %d\n", A.x);
	//	printf("A.y %d\n", A.y);
		A.x = floor(A.x / 64);
		A.y = floor(A.y / 64);
		if (map[A.x][A.y] != 0)
		{
			h = 1;
		//	printf("adf");
			A.x = A.x * 64;
			A.y = A.y * 64;
			break ;
		}
	//	printf("adfad");
		A.x = A.x * 64;
		A.y = A.y * 64;
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
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
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
	int start;

	p.x = (64 * 7);
	p.y = (64 * 15);
	p.view = 90;
	m.mlx = mlx_init();
	m.win = mlx_new_window(m.mlx, WINWIDTH, WINHEIGHT , "wolf3D");
  	planedst = (WINWIDTH / tan(FOV/2));
	rayangle = 5;
	ray = p.view + (FOV / 2);


	color = 0x00FFFFFF;
	slice_width	= rayangle;
		slice.x0 = 0; 			//collumn
		slice.x1 = slice.x0;
	while (slice.x0 < WINWIDTH)
	{

		hh = find_h_hit(ray, p, map);
		hv = find_v_hit(ray, p, map);
		//hh = hv;
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
		slice_height = (64/walldst) * 277;
		slice.y0 = (WINHEIGHT / 2) - (slice_height); //slice_start
		slice.y1 = slice.x0 + slice_height;
	//	printf("# walldst %d\n", walldst);
	////	printf("# slice_height %d\n", slice_height);
	//	printf("# slice.y0 %d\n", slice.y0);
	//	printf("# slice.y1 %d\n", slice.y1);
		k  = 0;
		while (k < slice_width)
		{
			start = slice.y0;
			while (start < slice.y1)
			{
				mlx_pixel_put(m.mlx, m.win, slice.x0, start, 0x00FFFFFF);
				start++;
			}
			slice.x0++;
			k++;
		}
	//	printf("slice.x0# %d\n", slice.x0);
		ray--;
	//	printf("ray# %d\n", ray);
	}
		
	mlx_loop(m.mlx);

	return (0);
}
