/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalp <yalp@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:59:47 by yalp              #+#    #+#             */
/*   Updated: 2025/05/22 17:15:03 by yalp             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

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

void init_idents(t_cube *cube, char *line, int id)
{
    char *value;
    if (id >= 1 && id <= 4)
        value = trim_spaces(line + 3); // "NO ", "SO ", "EA ", "WE "
    else if (id == 5 || id == 6)
        value = trim_spaces(line + 2); // "F ", "C "
    else
        return;

    if (id == 1)
        cube->texture_n = strdup(value);
    else if (id == 2)
        cube->texture_s = strdup(value);
    else if (id == 3)
        cube->texture_e = strdup(value);
    else if (id == 4)
        cube->texture_w = strdup(value);
    else if (id == 5)
        cube->color_f = strdup(value);
    else if (id == 6)
        cube->color_c = strdup(value);
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
        else if ((cube->all_of_file[i][0] == '1' || cube->all_of_file[i][0] == '0'))
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
    end(&cube);
    //init_mlx(&cube);

    return (0);
}