/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syoung <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/07/17 07:07:42 by syoung            #+#    #+#             */
/*   Updated: 2017/07/17 07:07:43 by syoung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

static void		ft_read_count(char *file, t_read *r)
{
	int space;

	space = 0;
	r->row_count = 0;
	r->col_count = 0;
	r->fd = open(file, O_RDONLY);
	if (get_next_line(r->fd, &r->row))
		r->row_count++;
	while (r->row[r->col_count])
	{
		if (r->row[r->col_count] == 32)
			space++;
		r->col_count++;
	}
	free(r->row);
	r->col_count -= space;
	while (get_next_line(r->fd, &r->row))
	{
		r->row_count++;
		free(r->row);
	}
	close(r->fd);
}

void			ft_read(char *file, t_draw *d)
{
	t_read r;

	r.i = 0;
	r.j = 0;
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
