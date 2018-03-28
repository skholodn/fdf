/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/11 14:55:55 by skholodn          #+#    #+#             */
/*   Updated: 2017/02/22 17:41:41 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		my_key_func(int keycode, t_map *map)
{
	map->xy = get_rotation(keycode, map);
	map->xy = get_zoom(keycode, map);
	map = get_move(keycode, map);
	if (keycode == 53)
		exit(0);
	if (map->xy != NULL)
		make_change(map);
	return (0);
}

void	make_change(t_map *map)
{
	map->img = mlx_new_image(map->mlx, WINDOW_WIDTH, WINDOW_WIDTH);
	map->data = mlx_get_data_addr(map->img, &map->bpp, &map->size_line,
			&map->endian);
	model_creator(map, map->xy);
	mlx_put_image_to_window(map->mlx, map->win, map->img, 0, 0);
}

t_xy	*get_rotation(int keycode, t_map *map)
{
	if (keycode == 35)
		map->xy = apply_rotation(map, 5, 0, 0);
	else if (keycode == 41)
		map->xy = apply_rotation(map, -5, 0, 0);
	else if (keycode == 33)
		map->xy = apply_rotation(map, 0, -5, 0);
	else if (keycode == 39)
		map->xy = apply_rotation(map, 0, 5, 0);
	else if (keycode == 30)
		map->xy = apply_rotation(map, 0, 0, 5);
	else if (keycode == 42)
		map->xy = apply_rotation(map, 0, 0, -5);
	if (keycode == 35 || keycode == 41 || keycode == 33 ||
		keycode == 39 || keycode == 30 || keycode == 42)
		map->xy = apply_zoom(map, 0.0f);
	return (map->xy);
}

t_xy	*get_zoom(int keycode, t_map *map)
{
	if (keycode == 69)
		return (apply_zoom(map, 0.01f));
	else if (keycode == 78)
		return (apply_zoom(map, -0.01f));
	return (map->xy);
}

t_map	*get_move(int keycode, t_map *map)
{
	if (keycode == 126)
		return (apply_move(map, 0.0f, -50.0f));
	else if (keycode == 125)
		return (apply_move(map, 0.0f, 50.0f));
	else if (keycode == 123)
		return (apply_move(map, -50.0f, 0.0f));
	else if (keycode == 124)
		return (apply_move(map, 50.0f, 0.0f));
	return (map);
}
