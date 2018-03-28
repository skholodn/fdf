/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skholodn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 20:15:42 by skholodn          #+#    #+#             */
/*   Updated: 2017/02/22 17:08:22 by skholodn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_strnew(size_t size)
{
	char	*str;
	size_t	i;

	i = 0;
	if ((str = malloc(size + 1)) == NULL)
		return (NULL);
	while (i < size + 1)
		str[i++] = '\0';
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	ls1;
	size_t	ls2;
	size_t	i;
	size_t	j;
	char	*strnew;

	if (s1 && s2)
	{
		i = -1;
		ls1 = ft_strlen(s1);
		ls2 = ft_strlen(s2);
		strnew = ft_strnew(ls1 + ls2);
		if (!strnew)
			return (NULL);
		while (s1[++i])
			strnew[i] = s1[i];
		j = 0;
		while (s2[j])
			strnew[i++] = s2[j++];
		return (strnew);
	}
	return (NULL);
}

int		main(int argc, char **argv)
{
	int		fd;
	char	*map;
	char	c[1024];
	ssize_t	red;

	if (argc != 2)
		print_error("Need: <filename>.fdf\n");
	map = ft_strnew(0);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1 || fd == 0)
	{
		write(1, "READING ERROR!\n", 15);
		return (-1);
	}
	while ((red = read(fd, c, 1023)))
	{
		c[red] = '\0';
		map = ft_strjoin(map, c);
	}
	ft_fdf(map);
	return (0);
}
