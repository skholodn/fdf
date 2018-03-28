/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 20:03:29 by skholodn          #+#    #+#             */
/*   Updated: 2017/02/22 17:22:04 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <mlx.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

# define ABS(x) 	(x < 0 ? -(x) : (x))

typedef struct		s_xy
{
	float			x;
	float			y;
	float			*rgb;
}					t_xy;

typedef struct		s_point
{
	float			*cord;
	float			*rgb;
	int				len_x;
	int				len_y;
}					t_point;

typedef struct		s_map
{
	t_point			*p;
	void			*mlx;
	void			*win;
	void			*img;
	char			*data;
	int				bpp;
	int				size_line;
	int				endian;
	t_xy			*xy;
	float			move_x;
	float			move_y;
}					t_map;

# define WINDOW_WIDTH 1600
# define WINDOW_HEIGHT 800

# define RAD 		0.01745f

typedef struct		s_line
{
	int				dx;
	int				dy;
	int				sx;
	int				sy;
	int				err;
	int				e2;
}					t_line;

typedef struct		s_c
{
	float			c_a;
	float			c_b;
	float			c_g;
	float			s_a;
	float			s_b;
	float			s_g;
}					t_c;

# define DEFINE1	i < 2 && (*map == ' ' || *map == '-' || *map == '+')
# define DEFINE11	ft_isdigit(*(map + 1))
# define DEFINE2	ft_isdigit(*map)
# define DEFINE20	(*map >= 'A' && *map <= 'F')
# define DEFINE21	(*map >= 'a' && *map <= 'f')
# define DEFINE22	(*(map + 1) == '\0')
# define DEFINE3	(*map == ' ' || *map == '-' || *map == '+')
# define DEFINE31	ft_isdigit(*(map + 1))
# define DEFINE4	(str - 1) && *str == '0' && *(str - 1) == ','
# define DEFINE41	(*(str + 1) == 'x' || *(str + 1) == 'X')
# define DEFINE5	ft_isdigit(*str)
# define DEFINE51	((*str == '-' || *str == '+') && ft_isdigit(*(str + 1)))
# define DEFINE6	**str != ' ' && **str != ',' && **str != '\n'
# define DEFINE61	**str != '-' && ft_isdigit(**str)
# define DEFINE7	(**str != ',' && ft_isdigit(*((*str) - 1)))
# define DEFINE71	(*((*str) - 1) >= 'a' && *((*str) - 1) >= 'f')
# define DEFINE72	(*((*str) - 1) >= 'A' && *((*str) - 1) >= 'F')

# define C_X 		map->p[abgi[3]].cord[0]
# define C_Y 		map->p[abgi[3]].cord[1]
# define C_Z 		map->p[abgi[3]].cord[2]

int					*get_points(char *map);
void				create_point(t_point *point);
t_point				*init_point(int *ab);
t_map				*map_init(t_point *point);
void				ft_window_fdf(t_point *point);
int					test_long(char *map, int *ab);
void				ft_fdf(char *map);
int					ft_convert(char **str, int base, int n);
int					ft_atoi_base(char **str, int base);
void				ft_skip_atoi(char *str, t_point *point);
void				print_error(char *str);
size_t				ft_strlen(const char *s);
char				*ft_strnew(size_t size);
int					ft_isdigit(int c);
void				get_rgb(t_point *point, int color);
void				generate_xy(int *ab, t_point *point);
float				vector_len(float *xy);
float				*get_color_step(float *rgb, float len);
void				draw_line(t_map *map, t_xy *p1, t_xy *p2);
void				put_pixel(t_map *map, float *xyrgb, float *color_step);
void				model_creator(t_map *map, t_xy *p);
void				make_change(t_map *map);
int					my_key_func(int keycode, t_map *map);
t_xy				*get_rotation(int keycode, t_map *map);
t_xy				*get_zoom(int keycode, t_map *map);
t_xy				*apply_zoom(t_map *map, float zoom);
t_map				*get_move(int keycode, t_map *map);
t_map				*apply_move(t_map *map, float change_x, float change_y);
t_xy				*apply_rotation(t_map *map, int angle_x, int angle_y,
					int angle_z);
void				xy_init(t_map *map, t_xy **xy);
t_c					*init_c(int *abgi, t_c *c);
void				xyrgb_init(t_xy *p1, t_xy *p2, float *xyrgb, t_map *m);
void				draw_line_help(t_map *map, float *xyrgb, float *color_step,
					t_line *line);
void				ft_skip_atoi_help(char **str, int *ixy);

#endif
