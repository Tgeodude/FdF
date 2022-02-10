/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeodude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:52:08 by tgeodude          #+#    #+#             */
/*   Updated: 2021/12/02 16:02:55 by tgeodude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*line_next_end(char **line_next, char **line)
{
	char	*pointer_n;
	char	*clean;

	pointer_n = NULL;
	if (*line_next)
	{
		pointer_n = ft_strchr(*line_next, '\n');
		if (pointer_n)
		{
			clean = *line_next;
			*line_next = ft_strdup(++pointer_n);
			*pointer_n = '\0';
			*line = ft_strdup(clean);
			free(clean);
		}
		else
		{
			*line = *line_next;
			*line_next = NULL;
		}
	}
	else
		*line = ft_strdup("");
	return (pointer_n);
}

static char	*free_line(char *line)
{
	free(line);
	return (NULL);
}

static char	*line_start(int bf, int fd)
{
	char		buff[BUFFER_SIZE + 1];
	char		*pointer_n;
	char		*line;
	static char	*line_next;
	char		*clean;

	pointer_n = line_next_end(&line_next, &line);
	while (!pointer_n && bf && !line_next)
	{	
		bf = read(fd, buff, BUFFER_SIZE);
		if (bf <= 0 && *line == '\0')
			return (free_line(line));
		buff[bf] = '\0';
		pointer_n = ft_strchr(buff, '\n');
		if (pointer_n)
		{
			line_next = ft_strdup(++pointer_n);
			*pointer_n = '\0';
		}
		clean = line;
		line = ft_strjoin(line, buff);
		free(clean);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	return (line_start(1, fd));
}
