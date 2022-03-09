/*                                                                            */
/* ************************************************************************** */
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
	char	*str;
	int		fd;
	int		word;
	int		i;

	word = 0;
	fd = open(file, O_RDONLY);
	i = -1;
	str = get_next_line(fd);
	while (str[i])
	{
		while (str[i] == ' ' && str[i])
			i++;
		if (str[i])
			word++;
		while (str[i] != ' ' && str[i])
			i++;
	}
	free(str);
	close(fd);
	return (word);
}

int	map_height(char *file)
{
	int		i;
	int		fd;
	char	*s;

	i = 0;
	fd = open(file, O_RDONLY);
	s = get_next_line(fd);
	while (s)
	{
		free(s);
		i++;
		s = get_next_line(fd);
	}
	free(s);
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

void map_create(char *book, t_data *fdf)
{
	int		i;
	char	**str;
	char	**str1;
	char	*str3;
	int		j;
	int		fd;

	i = -1;
	fdf->map = (int **)malloc(sizeof(int *) * fdf->height);
	fd = open(book, O_RDONLY);
	while (i++, i < fdf->height)
	{
		fdf->map[i] = (int *)malloc(sizeof(int) * fdf->width);
		str3 = get_next_line(fd);
		str = ft_split(str3, ' ');
		if (i != 0)
		{
			check_len_s(str, str1);
			free_line(str1);
		}
		j = -1;
		while (j++, str[j])
			fdf->map[i][j] = ft_atoi(str[j]);
		if (i != fdf->height - 1)
			str1 = str;
		free(str3);
	}
	free_line(str);
	close(fd);
}
