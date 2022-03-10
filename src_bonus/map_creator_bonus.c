/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creator_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeodude <tgeodude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:05:37 by tgeodude          #+#    #+#             */
/*   Updated: 2022/03/10 20:06:01 by tgeodude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	free_line(char **big_str)
{
	int	i;

	i = 0;
	while (big_str[i] != NULL)
		free(big_str[i++]);
	free(big_str);
}

int	map_width(char *file)
{
	int		len;
	char	*arr;
	int		fd;
	int		i;
	int		words;

	len = 0;
	fd = open(file, O_RDONLY);
	arr = get_next_line(fd);
	words = 0;
	i = 0;
	while (arr[i])
	{
		while (arr[i] == ' ' && arr[i])
			i++;
		if (arr[i] && arr[i] != '\n')
			words++;
		while (arr[i] != ' ' && arr[i])
			i++;
	}
	free(arr);
	close(fd);
	return (words);
}

int	map_height(char *file)
{
	int		fd;
	int		counter;
	char	*str;

	counter = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit(0);
	str = get_next_line(fd);
	while (str != NULL)
	{
		counter++;
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (counter);
}

void	map_create_parse(char *str, int i, t_data *fdf)
{
	char	**big_str;
	int		j;

	j = 0;
	fdf->map[i] = (int *)malloc(sizeof(int) * fdf->width + 1);
	big_str = ft_split(str, ' ');
	if (!fdf->map[i] || !big_str)
		exit (0);
	while (big_str[j] != NULL && big_str[j] != 0 && big_str[j][0] != '\n' \
		&& big_str[j][0] != ' ')
	{
		fdf->map[i][j] = ft_atoi(big_str[j]);
		j++;
	}
	if (j < fdf->width)
	{
		write(1, "Error\n", 6);
		exit (0);
	}
	free_line(big_str);
	free(str);
}

void	map_create(char *file, t_data *fdf)
{
	int		fd;
	int		i;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		exit(0);
	fdf->map = (int **)malloc(sizeof(int *) * fdf->height + 1);
	if (!fdf->map)
		exit(0);
	while (i < fdf->height)
	{
		map_create_parse(get_next_line(fd), i, fdf);
		i++;
	}
	fdf->map[i] = NULL;
}
