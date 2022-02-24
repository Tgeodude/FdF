/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creator.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeodude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/24 20:06:31 by tgeodude          #+#    #+#             */
/*   Updated: 2022/02/24 20:06:55 by tgeodude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "fdf.h"

int	map_width(char *book)
{
	char	*str;
	int		fd;
	int		word;

	word = 0;
	fd = open(book, O_RDONLY);
	str = get_next_line(fd);
	while (*str)
	{
		while (*str == ' ' && *str)
			str++;
		if (*str)
			word++;
		while (*str != ' ' && *str)
			str++;
	}
	close(fd);
	return (word);
}

int	map_height(char *book)
{
	int		i;
	int		fd;

	i = 0;
	fd = open(book, O_RDONLY);
	while (get_next_line(fd))
		i++;
	close(fd);
	return (i);
}

int	**map_create(char	*book, t_data fdf)
{
	int		**map;
	int		i;
	char	**str;
	int		j;
	int		fd;

	i = -1;
	map = (int **)malloc(sizeof(int *) * fdf.height);
	fd = open(book, O_RDONLY);
	while (i++, i < fdf.height)
	{
		map[i] = (int *)malloc(sizeof(int) * fdf.width);
		str = ft_split(get_next_line(fd), ' ');
		j = -1;
		while (j++, str[j])
			map[i][j] = ft_atoi(str[j]);
	}
	close(fd);
	return (map);
}
