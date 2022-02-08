#include "fdf.h"

int	width_sum(int fd)
{
	char	*arr;
	int	word;

	word = 0;
	arr = get_next_line(fd);
	while (*arr)
	{
		while (*arr == ' ' && *arr)
                        arr++;
                if (arr)
                        words++;
                while (*arr != ' ' && *arr)
                        arr++;
	}
	return (word)

}

int	height_sum(int fd)
{
	int word;

	word = 0;
	while (get_next_line(fd))
		word++;
}

int main(void)
{
	t_data *fdf;

	fd = open(file, O_RDONLY);
	fdf.width = width_sum(fd);
	fdf.height = height_sum(fd);
}
