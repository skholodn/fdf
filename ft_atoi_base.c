/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/22 17:28:04 by skholodn          #+#    #+#             */
/*   Updated: 2017/02/22 17:35:15 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		ft_convert(char **str, int base, int n)
{
	int r;

	r = 0;
	while (**str)
	{
		if ((**str < '0' || **str > ((base / 10) ? '9' : '/' + base))
				&& (**str < 'A' || **str > ((base / 10) ? '6' + base : '@'))
				&& (**str < 'W' || **str > ((base / 10) ? 'V' + base : '\'')))
			return (r * n);
		if (**str > '/' && **str < ':')
			r = r * base + **str - '0';
		else if (**str >= 'A' && **str <= 'F')
			r = r * base + (**str - 'A') + 10;
		else
			r = r * base + (**str - 'a') + 10;
		(*str)++;
	}
	return (r * n);
}

int		ft_atoi_base(char **str, int base)
{
	int		n;

	n = 1;
	while (**str == ' ' || (**str >= 9 && **str <= 13))
		(*str)++;
	if (**str == '-' && base == 10)
	{
		n = -1;
		(*str)++;
	}
	else if (**str == '+' && base == 10)
		(*str)++;
	while (**str == '0')
		(*str)++;
	return (ft_convert(str, base, n));
}

void	print_error(char *str)
{
	write(1, str, ft_strlen(str));
	exit(-1);
}

void	ft_skip_atoi_help(char **str, int *ixy)
{
	if (DEFINE6 && DEFINE61)
		print_error("NOT VALID MAP!\n");
	if (**str == '\n')
	{
		ixy[1] = 0;
		ixy[2]++;
	}
	(DEFINE7 || DEFINE71 || DEFINE72) ? ixy[0]++ : 0;
	(*str)++;
}

void	ft_skip_atoi(char *str, t_point *point)
{
	static int	ixy[3] = {0, 0, 0};

	while (*str)
	{
		if (DEFINE4 && DEFINE41)
		{
			str += 2;
			get_rgb(&point[ixy[0]], ft_atoi_base(&str, 16));
		}
		else if (DEFINE5 || DEFINE51)
		{
			point[ixy[0]].cord[0] = (float)(ixy[1])++;
			point[ixy[0]].cord[1] = (float)(ixy[2]);
			point[ixy[0]].cord[2] = (float)ft_atoi_base(&str, 10);
		}
		else
		{
			ft_skip_atoi_help(&str, ixy);
		}
	}
}
