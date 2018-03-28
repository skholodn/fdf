/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   points_cord.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 19:28:47 by skholodn          #+#    #+#             */
/*   Updated: 2017/02/22 19:29:06 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	model_creator(t_map *map, t_xy *p)
{
	int		i;
	int		points;

	i = 0;
	points = (map->p[0].len_x * map->p[0].len_y);
	while (i < points - 1)
	{
		if (i >= (points - map->p[0].len_x) && (i + 1) < points)
			draw_line(map, &p[i], &p[i + 1]);
		else if ((i + 1) % map->p[0].len_x == 0 && (i + 1) != points)
			draw_line(map, &p[i], &p[i + map->p[0].len_x]);
		else
		{
			draw_line(map, &p[i], &p[i + map->p[0].len_x]);
			draw_line(map, &p[i], &p[i + 1]);
		}
		i++;
	}
}

void	create_point(t_point *point)
{
	point->cord = malloc(sizeof(float) * 4);
	point->cord[3] = 1.0f;
	point->cord[2] = 0.0f;
	point->cord[1] = 0.0f;
	point->cord[0] = 0.0f;
	point->rgb = malloc(sizeof(float) * 3);
	point->rgb[0] = 255.0f;
	point->rgb[1] = 255.0f;
	point->rgb[2] = 255.0f;
	point->len_x = 0;
	point->len_y = 0;
}

t_point	*init_point(int *ab)
{
	t_point	*point;
	int		i;

	i = 0;
	point = (t_point*)malloc(sizeof(t_point) * (ab[0] * ab[1]));
	while (i < (ab[0] * ab[1]))
		create_point(&point[i++]);
	return (point);
}

t_map	*map_init(t_point *point)
{
	t_map	*map;

	if (!(map = malloc(sizeof(t_map))))
		return ((void*)0);
	map->move_x = 0.0f;
	map->move_y = 0.0f;
	map->p = point;
	map->mlx = mlx_init();
	map->win = mlx_new_window(map->mlx, WINDOW_WIDTH, WINDOW_HEIGHT,
		"skholod FDF");
	map->img = mlx_new_image(map->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	map->data = mlx_get_data_addr(map->img, &(map->bpp),
			&(map->size_line), &(map->endian));
	map->xy = NULL;
	return (map);
}
