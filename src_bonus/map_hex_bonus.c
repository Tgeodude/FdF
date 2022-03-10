/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_hex_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeodude <tgeodude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 20:11:11 by tgeodude          #+#    #+#             */
/*   Updated: 2022/03/10 20:11:14 by tgeodude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	check_map_color(t_data *fdf, char *s)
{
	int		i;
	int		j;
	char	*s1;
	int		color;

	i = 0;
	j = 0;
	while (s[i] != 'x')
		i++;
	i++;
	while (s[i + j] != ' ')
		j++;
	s1 = malloc(sizeof(char) * j);
	j = -1;
	while (j++, s[i + j] != ' ')
		s1[j] = s[i + j];
	fdf->flag_map_color = 1;
	color = convert_int(s1, j);
	free(s1);
	return (color);
}

int	convert_int(char *s, int size)
{
	int	i;
	int	hex;
	int	dec;

	i = -1;
	dec = 0;
	hex = 1;
	while (size--, size != 0)
		hex *= 16;
	while (i++, s[i])
	{
		dec += dec_hex(s[i]) * hex;
		hex /= 16;
	}
	return (dec);
}

int	map_contein_color(char *s, int place)
{
	char	*s1;
	int		n1;
	int		j;
	int		size;

	j = 0;
	while (s[j + place] != ' ' && s[j + place] != '\0')
		j++;
	size = j;
	s1 = malloc(sizeof(char) * j);
	n1 = -1;
	j = -1;
	while (j++, ++n1 < size)
		s1[n1] = s[j + place];
	size = convert_int(s1, size);
	free(s1);
	return (size);
}

int	found_hex(char *s, int j)
{
	while (s[j] != 'x')
		j++;
	j++;
	return (j);
}

void	map_parse(char *book, t_data *fdf)
{
	char	*s;
	int		fd;
	int		i;
	int		j;
	int		a;

	fd = open(book, O_RDONLY);
	fdf->map_hex = (int **) malloc(sizeof(int *) * fdf->height);
	i = -1;
	while (i++, i < fdf->height)
	{
		s = get_next_line(fd);
		a = 0;
		j = 0;
		fdf->map_hex[i] = malloc(sizeof(int) * fdf->width);
		while (a < fdf->width)
		{
			j = found_hex(s, j);
			fdf->map_hex[i][a++] = map_contein_color(s, j);
			while (s[j] != ' ' && a < fdf->width)
				j++;
		}
		free(s);
	}
	close(fd);
}
