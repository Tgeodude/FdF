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
#include "fdf_bonus.h"

int	map_width(char *book)
{
	char	*str;
	int		fd;
	int		word;
	int		i;

	word = 0;
	fd = open(book, O_RDONLY);
	i = -1;
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

void	check_len_s(char **s1, char **s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] && s1[i][0] != '\n')
		i++;
	while (s2[j] && s2[j][0] != '\n')
		j++;
	if (i != j)
	{
		write(1, "Error\n", 6);
		exit(0);
	}
}

int	**map_create(char	*book, t_data fdf)
{
	int		**map;
	int		i;
	char	**str;
	char	**str1;
	int		j;
	int		fd;

	i = -1;
	map = (int **)malloc(sizeof(int *) * fdf.height);
	fd = open(book, O_RDONLY);
	while (i++, i < fdf.height)
	{
		map[i] = (int *)malloc(sizeof(int) * fdf.width);
		str = ft_split(get_next_line(fd), ' ');
		if (i != 0)
			check_len_s(str, str1);
		j = -1;
		while (j++, str[j])
			map[i][j] = ft_atoi(str[j]);
		str1 = str;
	}
	close(fd);
	return (map);
}
