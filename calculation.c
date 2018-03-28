/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculation.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 13:23:27 by skholodn          #+#    #+#             */
/*   Updated: 2017/02/22 17:22:29 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		xy_init(t_map *map, t_xy **xy)
{
	int		i;

	i = -1;
	*xy = malloc(sizeof(t_xy) * (map->p[0].len_x * map->p[0].len_y));
	while (++i < (map->p[0].len_x * map->p[0].len_y))
	{
		(*xy)[i].x = map->p[i].cord[0];
		(*xy)[i].y = map->p[i].cord[0];
		(*xy)[i].rgb = malloc(sizeof(float) * 3);
		(*xy)[i].rgb[0] = map->p[i].rgb[0];
		(*xy)[i].rgb[1] = map->p[i].rgb[1];
		(*xy)[i].rgb[2] = map->p[i].rgb[2];
	}
}

t_c			*init_c(int *abgi, t_c *c)
{
	c->c_a = cosf(abgi[0] * RAD);
	c->c_b = cosf(abgi[1] * RAD);
	c->c_g = cosf(abgi[2] * RAD);
	c->s_a = sinf(abgi[0] * RAD);
	c->s_b = sinf(abgi[1] * RAD);
	c->s_g = sinf(abgi[2] * RAD);
	return (c);
}

t_xy		*apply_rotation(t_map *map, int angle_x, int angle_y, int angle_z)
{
	static int	abgi[] = {0, 0, 0, -1};
	t_c			*c;

	if (map->xy == NULL)
		xy_init(map, &map->xy);
	abgi[0] += angle_x;
	abgi[1] += angle_y;
	abgi[2] += angle_z;
	abgi[3] = -1;
	c = malloc(sizeof(t_c));
	c = init_c(abgi, c);
	while (++abgi[3] < (map->p[0].len_x * map->p[0].len_y))
	{
		map->xy[abgi[3]].x = (C_X * c->c_b * c->c_g + C_Y * c->c_b
				* -c->s_g + C_Z * -c->s_b);
		map->xy[abgi[3]].y = (C_X * (c->s_a * c->s_b * c->c_g + c->c_a
					* c->s_g) + C_Y * (c->s_a * c->s_b * -c->s_g
					+ c->c_a * c->c_g) + C_Z * c->s_a * c->c_b);
	}
	free(c);
	return (map->xy);
}

t_xy		*apply_zoom(t_map *map, float zoom)
{
	static int	i = -1;
	float		z;

	z = 1;
	if (map->xy == NULL)
		xy_init(map, &map->xy);
	z += zoom;
	i = -1;
	while (++i < (map->p[0].len_x * map->p[0].len_y))
	{
		map->p[i].cord[0] *= z;
		map->p[i].cord[1] *= z;
		map->p[i].cord[2] *= z;
		map->xy[i].x *= z;
		map->xy[i].y *= z;
	}
	return (map->xy);
}

t_map		*apply_move(t_map *map, float change_x, float change_y)
{
	map->move_x += change_x;
	map->move_y += change_y;
	return (map);
}
