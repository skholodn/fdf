/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/10 09:28:36 by skholodn          #+#    #+#             */
/*   Updated: 2017/02/22 18:00:51 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		*get_points(char *map)
{
	int			*ab;
	static int	i = 0;

	ab = (int*)malloc(2 * sizeof(int));
	ab[0] = 0;
	ab[1] = 0;
	if (map[0] == ' ' || map[0] == '-' || map[0] == '+')
		i = 1;
	while (*map)
	{
		if (DEFINE1 && DEFINE11)
			ab[0]++;
		if (*map == '\n')
		{
			i += 2;
			ab[1]++;
		}
		if ((DEFINE2 || DEFINE20 || DEFINE21) && DEFINE22)
			ab[1]++;
		map++;
	}
	if (i % 2 != 1)
		ab[0]++;
	return (ab);
}

void	ft_window_fdf(t_point *point)
{
	t_map	*map;

	if (!(map = map_init(point)))
		print_error("ERROR WINDOW CREATION!!!\n");
	map->xy = apply_rotation(map, 0, 0, 0);
	model_creator(map, map->xy);
	mlx_put_image_to_window(map->mlx, map->win, map->img, 0, 0);
	mlx_hook(map->win, 2, 5, my_key_func, map);
	mlx_loop(map->mlx);
}

int		test_long(char *map, int *ab)
{
	int		a;
	int		x;

	x = 0;
	a = 0;
	(map[0] == ' ' || map[0] == '-' || map[0] == '+') ? a = 1 : 0;
	while (*map)
	{
		if (DEFINE3 && DEFINE31)
			x++;
		if (*map == '\n')
		{
			(a != 1) ? x++ : 0;
			if (x != ab[0])
				return (1);
			x = 0;
		}
		map++;
	}
	(a != 1) ? x++ : 0;
	if (x != ab[0] && *(map - 1) != '\n')
		return (1);
	return (0);
}

void	ft_fdf(char *map)
{
	int		*ab;
	t_point	*point;

	ab = get_points(map);
	if (test_long(map, ab))
		print_error("WRONG MAP!!!\n");
	point = init_point(ab);
	ft_skip_atoi(map, point);
	generate_xy(ab, point);
	free(map);
	free(ab);
	ft_window_fdf(point);
}
