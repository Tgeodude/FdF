#include "fdf_bonus.h"

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
    color = convert_int(s1, j);
    free(s1);
    return (color);
}

int check_map_on_hex(char *book, t_data *fdf)
{
    int fd;
    char    *s;
    int     j;
    int     mach;
	
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

int convert_int(char *s, int size)
{
    int i;
    int hex;
    int dec;

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

int   map_contein_color(char *s, int place)
{
    char    *s1;
    int     n1;
    int     j;
    int     size;

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

int     found_hex(char *s)
{
    int i;
    int count;
    
    i = -1;
    count = 0;
    while (i++, s[i])
        if (s[i] == 'x')
            count++;
    return (count);
}

void    map_parse(char  *book, t_data *fdf)
{
    char            *s;
    int             fd;
    int             i;
    int             j;
    int             a;
    int             count;

    fd = open(book, O_RDONLY);
    fdf->map_hex = (int**)malloc(sizeof(int*) * fdf->height);
    i = -1;
    while (i++, i < fdf->height)
    {
        s = get_next_line(fd);
        a = 0;
        j = 0;
        fdf->map_hex[i] = malloc(sizeof(int) * fdf->width);
        count = found_hex(s);
        while (a < fdf->width)
        {
            while (s[j] != 'x')
                j++;
            j++;
            fdf->map_hex[i][a] = map_contein_color(s, j);
            a++;
            while (s[j] != ' ' && a < fdf->width)
                j++;
        }
        free(s);
    }
    close(fd);
}