/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_hex_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeodude <tgeodude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 19:15:49 by tgeodude          #+#    #+#             */
/*   Updated: 2022/03/10 19:56:52 by tgeodude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	validation_of_file(int argc, char **argv)
{
	if (argc != 2)
	{
		write(1, "Error\n", 6);
		exit(0);
	}
	if ((ft_strnstr((const char *)(argv[1]), ".fdf", 20000)) == NULL)
	{
		write(1, "Error\n", 6);
		exit(0);
	}
}

int	check_map_on_hex(char *book, t_data *fdf)
{
	int		fd;
	char	*s;
	int		j;
	int		mach;

	fd = open(book, O_RDONLY);
	j = -1;
	while (j++, j < (fdf->height - 1))
	{
		s = get_next_line(fd);
		if (j == 0 && ft_strchr(s, 'x'))
		{
			free(s);
			return (1);
		}
		if (ft_strchr(s, 'x') && j > 0)
		{
			mach = check_map_color(fdf, s);
			free(s);
			return (mach);
		}
		free(s);
	}
	close(fd);
	return (0);
}

int	dec_hex_ab(char c)
{
	if (c == 'a' || c == 'A')
		return (10);
	if (c == 'b' || c == 'B')
		return (11);
	if (c == 'c' || c == 'C')
		return (12);
	if (c == 'd' || c == 'D')
		return (13);
	if (c == 'e' || c == 'E')
		return (14);
	if (c == 'f' || c == 'F')
		return (15);
	return (-1);
}

int	dec_hex(char c)
{
	if (c == '0')
		return (0);
	if (c == '1')
		return (1);
	if (c == '2')
		return (2);
	if (c == '3')
		return (3);
	if (c == '4')
		return (4);
	if (c == '5')
		return (5);
	if (c == '6')
		return (6);
	if (c == '7')
		return (7);
	if (c == '8')
		return (8);
	if (c == '9')
		return (9);
	return (dec_hex_ab(c));
}

int	dis_check(int x, int y)
{
	if (x >= 2560 || y >= 1600)
		return (-1);
	if (x < 0 || y < 0)
		return (-1);
	return (0);
}
