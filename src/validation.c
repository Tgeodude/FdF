/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeodude <tgeodude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 17:53:49 by tgeodude          #+#    #+#             */
/*   Updated: 2022/03/10 17:53:53 by tgeodude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	my_pixel_put(t_data *fdf, int x, int y, int color)
{
	char	*dst;

	dst = fdf->addres + (y * fdf->line_length + x * (fdf->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	dis_check(int x, int y)
{
	if (x >= 2560 || y >= 1600)
		return (-1);
	if (x < 0 || y < 0)
		return (-1);
	return (0);
}
