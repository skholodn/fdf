/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 19:07:06 by skholodn          #+#    #+#             */
/*   Updated: 2017/02/22 19:27:41 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	get_rgb(t_point *point, int color)
{
	point->rgb[0] = (float)((color & 0xFF0000) >> 16);
	point->rgb[1] = (float)((color & 0xFF00) >> 8);
	point->rgb[2] = (float)((color & 0xFF));
}

float	vector_len(float *xy)
{
	float	x;
	float	y;

	x = xy[2] - xy[0];
	y = xy[3] - xy[1];
	return (sqrtf(x * x + y * y));
}

float	*get_color_step(float *rgb, float len)
{
	float	*color_step;

	color_step = malloc(sizeof(float) * 3);
	color_step[0] = (rgb[7] - rgb[4]) / len;
	color_step[1] = (rgb[8] - rgb[5]) / len;
	color_step[2] = (rgb[9] - rgb[6]) / len;
	return (color_step);
}

void	draw_line_help(t_map *map, float *xyrgb, float *color_step,
						t_line *line)
{
	put_pixel(map, xyrgb, color_step);
	line->e2 = line->err * 2;
	if (line->e2 > -line->dx)
	{
		line->err -= line->dy;
		xyrgb[0] += line->sx;
	}
	if (line->e2 < line->dy)
	{
		line->err += line->dx;
		xyrgb[1] += line->sy;
	}
}

void	draw_line(t_map *map, t_xy *p1, t_xy *p2)
{
	t_line	line;
	float	xyrgb[12];
	float	*color_step;

	xyrgb_init(p1, p2, xyrgb, map);
	line.dx = ABS((int)(xyrgb[2] - xyrgb[0]));
	line.sx = xyrgb[0] < xyrgb[2] ? 1 : -1;
	line.dy = ABS((int)(xyrgb[3] - xyrgb[1]));
	line.sy = xyrgb[1] < xyrgb[3] ? 1 : -1;
	line.err = (line.dx > line.dy ? line.dx : -line.dy) / 2;
	color_step = get_color_step(xyrgb, vector_len(xyrgb));
	while (1)
	{
		draw_line_help(map, xyrgb, color_step, &line);
		if (xyrgb[0] == xyrgb[2] && xyrgb[1] == xyrgb[3])
			break ;
	}
	free(color_step);
}
