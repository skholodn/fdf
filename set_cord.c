/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cord.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 12:50:10 by skholodn          #+#    #+#             */
/*   Updated: 2017/02/22 19:26:07 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*
** max_xyz[0] == X, max_xyz[1] == Y, max_xyz[2] == Z,
*/

void	generate_xy(int *ab, t_point *point)
{
	int				i;
	static	float	max_xyz[] = {0.0f, 0.0f, 0.0f};

	max_xyz[0] = ((float)ab[0] - 1.0f);
	max_xyz[1] = ((float)ab[1] - 1.0f);
	i = -1;
	while (++i < (ab[0] * ab[1]))
		if ((ABS(point[i].cord[2]) - max_xyz[2]) > 0)
			max_xyz[2] = ABS(point[i].cord[2]);
	i = -1;
	while (++i < (ab[0] * ab[1]))
	{
		point[i].cord[0] -= (max_xyz[0] / 2.0f);
		point[i].cord[0] /= (max_xyz[0] / 2.0f);
		point[i].cord[1] -= (max_xyz[1] / 2.0f);
		point[i].cord[1] /= (max_xyz[1] / 2.0f);
		point[i].cord[2] ? point[i].cord[2] /= (max_xyz[2]) : 0;
		point[i].len_x = ab[0];
		point[i].len_y = ab[1];
	}
}

/*
** 0.01745329252 to transform angle to radians;
*/

void	put_pixel(t_map *map, float *xyrgb, float *color_step)
{
	int		cord;

	if (xyrgb[0] < WINDOW_WIDTH && xyrgb[1] < WINDOW_HEIGHT
			&& xyrgb[0] >= 0 && xyrgb[1] >= 0)
	{
		cord = (int)((xyrgb[1] * map->size_line) + (xyrgb[0] * map->bpp / 8));
		if (xyrgb[4] + color_step[0] >= 0 && xyrgb[4] + color_step[0] <= 255)
			xyrgb[4] += color_step[0];
		if (xyrgb[5] + color_step[1] >= 0 && xyrgb[5] + color_step[1] <= 255)
			xyrgb[5] += color_step[1];
		if (xyrgb[6] + color_step[2] >= 0 && xyrgb[6] + color_step[2] <= 255)
			xyrgb[6] += color_step[2];
		map->data[cord] = (char)xyrgb[6];
		map->data[cord + 1] = (char)xyrgb[5];
		map->data[cord + 2] = (char)xyrgb[4];
	}
}

void	xyrgb_init(t_xy *p1, t_xy *p2, float *xyrgb, t_map *m)
{
	xyrgb[10] = m->move_x;
	xyrgb[11] = m->move_y;
	xyrgb[0] = (int)((p1->x * 300 * 0.5f + 0.5f) + xyrgb[10]
			+ (float)WINDOW_WIDTH / 2.0f);
	xyrgb[1] = (int)((p1->y * 300 * 0.5f + 0.5f) + xyrgb[11]
			+ (float)WINDOW_HEIGHT / 2.0f);
	xyrgb[2] = (int)((p2->x * 300 * 0.5f + 0.5f) + xyrgb[10]
			+ (float)WINDOW_WIDTH / 2.0f);
	xyrgb[3] = (int)((p2->y * 300 * 0.5f + 0.5f) + xyrgb[11]
			+ (float)WINDOW_HEIGHT / 2.0f);
	xyrgb[4] = p1->rgb[0];
	xyrgb[5] = p1->rgb[1];
	xyrgb[6] = p1->rgb[2];
	xyrgb[7] = p2->rgb[0];
	xyrgb[8] = p2->rgb[1];
	xyrgb[9] = p2->rgb[2];
}

/*
** xyrgb[0] = x1, xyrgb[1] = y1, xyrgb[2] = x2, xyrgb[3] = y2,
** xyrgb[4] = r1, xyrgb[5] = g1, xyrgb[6] = b1,
** xyrgb[7] = r2, xyrgb[8] = g2, xyrgb[9] = b2,
** xyrgb[10] = x+-, xyrgb[11] = y+-;
*/
