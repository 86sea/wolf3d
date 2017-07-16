#include "wolf3d.h"

static void	ft_read_count(char *file, t_read *r)
{
	r->i = 0;
	r->j = 0;
	r->row_count = mapHeight;
	r->col_count = mapWidth;
	//r->fd = open(file, O_RDONLY);
	//while (read(r->fd, r->buff, 1))
	//	if (r->buff[0] == '\n')
	//		r->row_count++;
	///close(r->fd);
} 

void			ft_read(char *file, t_draw *d)
{
	t_read r;

	ft_read_count(file, &r);
	r.fd = open(file, O_RDONLY);
	d->map = (int **)malloc(sizeof(int *) * (r.row_count + 1));
	while (get_next_line(r.fd, &r.row))
	{
		r.split = ft_strsplit((const char*)r.row, ' ');
		free(r.row);
		while (r.split[r.col_count] != NULL)
			r.col_count++;
		r.j = 0;
		d->map[r.i] = (int *)malloc(sizeof(int) * (r.col_count + 1));
		while (r.split[r.j] != NULL)
		{
			d->map[r.i][r.j] = ft_atoi((const char*)r.split[r.j]);
			free(r.split[r.j]);
			r.j++;
		}
		free(r.split);
		r.i++;
	}

	close(r.fd);
}