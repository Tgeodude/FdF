#include "fdf.h"

int    check_map_color(t_data *fdf, char *s)
{
    int     i;
    int     j;
    char    *s1;
    int     color;

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
    color = convert_int(s1);
    free(s1);
    return (color);
}

int check_map_on_hex(char *book, t_data *fdf)
{
    int     fd;
    char    *s;
    int     j;
	
    fd = open(book, O_RDONLY);
    s = get_next_line(fd);
    j = -1;
    while (j++, j < (fdf->height - 1))
    {
        s = get_next_line(fd);
        if (ft_strchr(s, 'x') && j == 0)
            return (1);
        if (ft_strchr(s, 'x') && j > 0)
            return (check_map_color(fdf, s));
        free(s);
    }
    close(fd);
    return (0);
}

void    validation_of_file(int argc, char **argv)
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

int dec_hex_ab(char c)
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

int dec_hex(char c)
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

int convert_int(char *s)
{
    int i;
    int hex;
    int dec;

    i = 0;
    dec = 0;
    hex = 1;
    while (s[i])
        i++;
    while (i--, i != 0)
        hex *= 16;
    while (i++, s[i])
    {
        dec += dec_hex(s[i]) * hex;
        hex /= 16;
    }
    return (dec);
}

int   map_contein_color(char *s)
{
    char    *s1;
    int     n;
    int     n1;
    int     j;
    int     i;

    j = 0;
    while (s[j] != 'x' && s[j])
        j++;
    n = 0;
    while (s[j + n] != ' ' && s[j + n])
        n++;
    s1 = malloc(sizeof(char) * (n - 1));
    n1 = -1;
    while (j++, ++n1 < (n - 1))
        s1[n1] = s[j];
    i = convert_int(s1);
    free(s1);
    return (i);
}

int    **map_parse(char  *book, t_data *fdf)
{
    char            *s;
    int             fd;
    int             i;
    int             j;
    int             a;
    int            **map_hex;

    fd = open(book, O_RDONLY);
    map_hex = (int**)malloc(sizeof(int*) * fdf->height);
    i = -1;
    while (i++, i < fdf->height)
    {
        j = -1;
        s = get_next_line(fd);
        a = 0;
        map_hex[i] = malloc(sizeof(int) * fdf->width);
        while (j++, j < fdf->width)
        {
            map_hex[i][a] = map_contein_color(s);
            a++;
        }
        free(s);
    }
    close(fd);
    return (map_hex);
}