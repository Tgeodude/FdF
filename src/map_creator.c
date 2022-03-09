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
	int		fd;
	int		counter;
	char	**split_str;
	char	*str;

	counter = 0;
	fd = open(file, O_RDONLY);
	str = get_next_line(fd);
	split_str = ft_split(str, ' ');
	while (split_str[counter] != NULL)
		counter++;
	free(str);
	free_line(split_str);	
	close(fd);
	return (counter);
}

int	map_height(char *file)
{
	int		fd;
	int		counter;
	char	*str;

	counter = 0;
	fd = open(file, O_RDONLY);
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
	while (big_str[j] != NULL && big_str[j] != 0 && big_str[j][0] != '\n' \
		&& big_str[j][0] != ' ')
	{
		fdf->map[i][j] = ft_atoi(big_str[j]);
		j++;
	}
	if (j < fdf->width)
	{
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
