/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalp <yalp@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:59:47 by yalp              #+#    #+#             */
/*   Updated: 2025/05/28 19:06:13 by yalp             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 1;
	while (str[i] == 32 || (str[i] <= 13 && str[i] >= 9))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			k = -1;
		i++;
	}
	while ((str[i] <= 57 && str[i] >= 48))
	{
		j = j * 10 + (str[i] - 48);
		i++;
	}
	return (k * j);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t		a;
	size_t		slen;
	char		*str;

	slen = strlen(s);
	a = 0;
	if (len > slen - start)
		len = slen - start;
	if (start >= slen)
	{
		str = malloc(sizeof(char));
		str[0] = '\0';
		return (str);
	}
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (0);
	while (a < len)
	{
		str[a] = s[start + a];
		a++;
	}
	str[a] = '\0';
	return (str);
}

static int	cw(char const *str, char c)
{
	int	count;

	count = 0;
	if (!*str)
		return (0);
	while (*str)
	{
		while (*str == c)
			str++;
		if (*str)
			count++;
		while (*str != c && *str)
			str++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	char		**words;
	long		wordlen;
	int			i;

	i = 0;
	words = (char **)malloc((cw(s, c) + 1) * sizeof(char *));
	if (!words || !s)
		return (0);
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			if (!strchr(s, c))
				wordlen = strlen(s);
			else
				wordlen = strchr(s, c) - s;
			words[i++] = ft_substr(s, 0, wordlen);
			s += wordlen;
		}
	}
	words[i] = NULL;
	return (words);
}

void end(t_cube *cube)
{
	int	i;

	i = 0;
	while (cube->all_of_file[i])
	{
		if (cube->all_of_file[i] != NULL)
			free(cube->all_of_file[i]);
		i++;
	}
	if (cube->all_of_file != NULL)
		free(cube->all_of_file);
	if (cube->texture_n != NULL)
		free(cube->texture_n);
	if (cube->texture_s != NULL)
		free(cube->texture_s);
	if (cube->texture_e != NULL)
		free(cube->texture_e);
	if (cube->texture_w != NULL)
		free(cube->texture_w);
	if (cube->color_f != NULL)
		free(cube->color_f);
	if (cube->color_c != NULL)
		free(cube->color_c);
	if (cube->values_c != NULL)
		free(cube->values_c);
	if (cube->values_f != NULL)
		free(cube->values_f);
	exit(EXIT_FAILURE);
}

void arg_check(int argc, char **argv)
{
	if (argc != 2)
	{
	fprintf(stderr, "Error: Wrong number of arguments\n");
	exit(EXIT_FAILURE);
	}
	if (argv[1][strlen(argv[1]) - 4] != '.')
	{
		fprintf(stderr, "Error: Invalid file extension\n");
		exit(EXIT_FAILURE);
	}
	if (strcmp(&argv[1][strlen(argv[1]) - 4], ".cub") != 0)
	{
		fprintf(stderr, "Error: Invalid file extension\n");
		exit(EXIT_FAILURE);
	}
	if (open(argv[1], O_RDONLY) < 0)
	{
		fprintf(stderr, "Error: File can not be read\n");
		exit(EXIT_FAILURE);
	}
}

void init_cube(t_cube *cube)
{
	cube->map = NULL;
	cube->texture_n = NULL;
	cube->texture_s = NULL;
	cube->texture_e = NULL;
	cube->texture_w = NULL;
	cube->color_f = NULL;
	cube->color_c = NULL;
	cube->all_of_file = NULL;
	cube->mlx = NULL;
	cube->win = NULL;
    cube->values_c = NULL;
    cube->values_f = NULL;
	cube->player_pov = 0;
	cube->width = 0;
	cube->height = 0;
	cube->count_n = 0;
	cube->count_s = 0;
	cube->count_e = 0;
	cube->count_w = 0;
	cube->count_f = 0;
	cube->count_c = 0;
}
void read_file(t_cube *cube, char *file)
{
    int		y;
	int		fd;
	int		i;
	char	*lines;

	i = 0;
	y = 0;
	fd = open(file, O_RDONLY);
	lines = get_next_line(fd);
	while (lines != NULL)
	{
		free(lines);
		lines = get_next_line(fd);
		y++;
	}	
	close(fd);
	cube->all_of_file = malloc(sizeof(char *) * (y + 1));
	fd = open(file, O_RDONLY);
	while (y > 0)
	{
		cube->all_of_file[i++] = get_next_line(fd);
		y--;
	}
	close(fd);
}
void init_mlx(t_cube *cube)
{
	cube->mlx = mlx_init();
	if (!cube->mlx)
	{
		fprintf(stderr, "Error: Failed to initialize mlx\n");
		exit(EXIT_FAILURE);
	}
	cube->win = mlx_new_window(cube->mlx, cube->width * 32, cube->height * 32, "Cub3D");
	if (!cube->win)
	{
		fprintf(stderr, "Error: Failed to create window\n");
		exit(EXIT_FAILURE);
	}
}
int is_ident_line(char *line)
{
	while (*line == ' '|| *line == '\t')
		line++;
	if (*line == 'N' && *(line + 1) == 'O')
		return (1);
	else if (*line == 'S' && *(line + 1) == 'O')
		return (2);
	else if (*line == 'E' && *(line + 1) == 'A')
		return (3);
	else if (*line == 'W' && *(line + 1) == 'E')
		return (4);
	else if (*line == 'F')
		return (5);
	else if (*line == 'C')
		return (6);
	else
		return (0);
}

// Satır başındaki boşlukları atla
char *skip_spaces(char *str)
{
    while (*str == ' ' || *str == '\t')
        str++;
    return str;
}

// Satır başındaki ve sonundaki boşlukları atla
char *trim_spaces(char *str)
{
    char *end;
    str = skip_spaces(str);
    if (*str == 0)
        return str;
    end = str + strlen(str) - 1;
    while (end > str && (*end == ' ' || *end == '\t' || *end == '\n'))
        end--;
    *(end + 1) = 0;
    return str;
}

int *init_values(char *color)
{
    char **rgb;
    int *values;
    int i;

    rgb = ft_split(color, ',');
    if (!rgb)
        return NULL;
    values = malloc(sizeof(int) * 3);
    if (!values)
    {
        free(rgb);
        return NULL;
    }
    i = 0;
    while (i < 3 && rgb[i])
    {
        values[i] = ft_atoi(rgb[i]);
        free(rgb[i]);
        i++;
    }
    free(rgb);
    return (values);
}

void init_idents(t_cube *cube, char *line, int id)
{
    char *value;

    value = trim_spaces(line);
    if (id == 1)
    cube->texture_n = strdup(skip_spaces(value + 2));
    else if (id == 2)
    cube->texture_s = strdup(skip_spaces(value + 2));
    else if (id == 3)
    cube->texture_e = strdup(skip_spaces(value + 2));
    else if (id == 4)
    cube->texture_w = strdup(skip_spaces(value + 2));
    else if (id == 5)
    {
        cube->color_f = strdup(skip_spaces(value + 1));
        cube->values_f = init_values(cube->color_f);
    }
    else if (id == 6)
    {
        cube->color_c = strdup(skip_spaces(value + 1));
        cube->values_c = init_values(cube->color_c);
    }
    else
        return;
}

// Satır tamamen boş mu kontrolü
int is_empty_line(char *line)
{
    while (*line)
    {
        if (*line != ' ' && *line != '\t' && *line != '\n')
            return (0);
        line++;
    }
    return (1);
}

// Dosya yolu kontrolü (en az bir karakter)
int is_valid_path(char *line)
{
    while (*line == ' ' || *line == '\t')
        line++;
    if (*line == '\0' || *line == '\n')
        return 0;
    return 1;
}

// RGB kontrolü (F ve C için) burayı hallediceem split ile virgüle göre bölüp sayıları kontrol edicem
int is_valid_rgb(char *line)
{
    char    **rgb;
    int     i;

    i = 0;
    rgb = ft_split(skip_spaces(skip_spaces(line) + 1 ), ',');
    if (!rgb)
        return (0);
    while (rgb[i])
        i++;;
    if (i != 3)
    {
        free(rgb);
        return 0;
    }
    i = 0;
    while (rgb[i])
    {
        if (ft_atoi(rgb[i]) < 0 || ft_atoi(rgb[i]) > 255)
        {
			i = 0;
            while(rgb[i])
				free(rgb[i++]);
			free(rgb);
            return 0;
        }
        i++;
    }
	i = 0;
	while(rgb[i])
		free(rgb[i++]);
	free(rgb);
    return (1);
}

void send_to_init(t_cube *cube, char *line, int id)
{
    if (id == 1) 
        cube->count_n++;
    else if (id == 2) 
        cube->count_s++;
    else if (id == 3) 
        cube->count_e++;
    else if (id == 4) 
        cube->count_w++;
    else if (id == 5) 
        cube->count_f++;
    else if (id == 6) 
        cube->count_c++;
    init_idents(cube, line, id);
}
int is_map_line(char *line)
{
    line = skip_spaces(line);
    return (*line == '1' || *line == '0');
}

void check_file(t_cube *cube)
{
    int i = 0;
    int map_started = 0;

    while (cube->all_of_file[i])
    {
        if (is_empty_line(cube->all_of_file[i]))
        {
            i++;
            continue;
        }
        int id = is_ident_line(cube->all_of_file[i]);
        if (!map_started && id)
        {
            char *content = cube->all_of_file[i] + 2;
            if (id >= 1 && id <= 4 && !is_valid_path(content))
            {
                fprintf(stderr, "Error: Invalid path for identifier: %s", cube->all_of_file[i]);
                end(cube);
            }
            if ((id == 5 || id == 6) && !is_valid_rgb(content))
            {
                fprintf(stderr, "Error: Invalid RGB value for identifier: %s", cube->all_of_file[i]);
                end(cube);
            }
			send_to_init(cube, cube->all_of_file[i], id);
        }
        else if (is_map_line(cube->all_of_file[i]))
            map_started = 1;
        else if (map_started && id)
        {
            fprintf(stderr, "Error: Identifier after map started: %s", cube->all_of_file[i]);
            end(cube);
        }
        else if (!map_started && !id)
        {
            fprintf(stderr, "Error: Invalid identifier or map line: %s", cube->all_of_file[i]);
            end(cube);
        }
        i++;
    }
    if (cube->count_n != 1 || cube->count_s != 1 || cube->count_e != 1 || cube->count_w != 1 || cube->count_f != 1 || cube->count_c != 1)
    {
        fprintf(stderr, "Error: Identifiers must be defined exactly once (NO:%d SO:%d EA:%d WE:%d F:%d C:%d)\n",
            cube->count_n, cube->count_s, cube->count_e, cube->count_w, cube->count_f, cube->count_c);
        end(cube);
    }
}

int main(int argc, char **argv)
{
    t_cube cube;

    int i = 0;
    arg_check(argc, argv);
    init_cube(&cube);
    read_file(&cube, argv[1]);
    check_file(&cube);
	printf("%s\n", cube.texture_n);
	printf("%s\n", cube.texture_s);
	printf("%s\n", cube.texture_e);
	printf("%s\n", cube.texture_w);
	printf("%s\n", cube.color_f);
	printf("%s\n", cube.color_c);
    printf("%d, %d, %d\n", cube.values_c[0], cube.values_c[1], cube.values_c[2]);
    printf("%d, %d, %d\n", cube.values_f[0], cube.values_f[1], cube.values_f[2]);
    end(&cube);
    //init_mlx(&cube);

    return (0);
}