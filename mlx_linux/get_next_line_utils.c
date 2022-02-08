/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgeodude <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 16:07:10 by tgeodude          #+#    #+#             */
/*   Updated: 2021/12/02 16:07:24 by tgeodude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dest, const void *src, size_t len)
{
	size_t			c;
	unsigned char	*tmp_0;
	unsigned char	*tmp_1;

	c = -1;
	tmp_0 = (unsigned char *)src;
	tmp_1 = (unsigned char *)dest;
	while (c++, c < len && ((unsigned char *)dest || (unsigned char *)src))
		tmp_1[c] = tmp_0[c];
	return (dest);
}

char	*ft_strdup(const char *s)
{
	char	*s2;
	size_t	i;

	i = -1;
	s2 = malloc(ft_strlen(s) + 1);
	if (!s2)
		return (NULL);
	while (i++, s[i])
		s2[i] = s[i];
	s2[i] = '\0';
	return (s2);
}

char	*ft_strchr(const char *string, int symbol)
{
	unsigned char	tmp;

	tmp = symbol;
	while (*string)
	{
		if (*string == tmp)
			return ((char *)string);
		string++;
	}
	if (symbol == '\0')
		return ((char *)(string + ft_strlen(string)));
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	i;
	size_t	j;

	if (!s1)
		return (NULL);
	s3 = (char *)malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!s3)
		return (NULL);
	i = -1;
	j = -1;
	while (i++, s1[i])
		s3[i] = s1[i];
	while (j++, s2[j])
	{
		s3[i] = s2[j];
		i++;
	}
	s3[i] = 0;
	return (s3);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
