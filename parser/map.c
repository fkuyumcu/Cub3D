/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalp <yalp@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:32:08 by yalp              #+#    #+#             */
/*   Updated: 2025/05/31 16:51:25 by yalp             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int find_largest_line(char **map)
{
	int i;
	int max_length;

	i = 0;
	max_length = 0;
	while (map[i] != NULL)
	{
		int length = strlen(map[i]);
		if (length > max_length)
			max_length = length;
		i++;
	}
	return (max_length);
}

void add_space_line(char ***map_ptr, int space_count, t_cube *cube)
{
    int i = 0;
    int old_len = 0;
    char **map = *map_ptr;
    char **new_map;
    char *space_line;

    // Eski satır sayısını bul
    while (map[old_len])
        old_len++;

    // Yeni map için yer ayır (2 satır fazla)
    new_map = malloc(sizeof(char *) * (old_len + 3));
    if (!new_map)
        put_error("Error: Memory allocation failed\n", cube);

    // Baştaki tamamen space olan satırı oluştur
    space_line = malloc(space_count + 1);
    if (!space_line)
        put_error("Error: Memory allocation failed\n", cube);
    memset(space_line, ' ', space_count);
    space_line[space_count] = '\n';
	space_line[space_count + 1] = '\0';

    new_map[0] = space_line;

    // Eski satırları kopyala
    for (i = 0; i < old_len; i++)
        new_map[i + 1] = map[i];

    // Sona tamamen space olan satırı ekle
    space_line = malloc(space_count + 1);
    if (!space_line)
        put_error("Error: Memory allocation failed\n", cube);
    memset(space_line, ' ', space_count);
	space_line[0] = '\n'; // düzelt
    space_line[space_count] = '\0';
    new_map[old_len + 1] = space_line;

    // Sonlandırıcı
    new_map[old_len + 2] = NULL;

    // Eski map pointer'ını güncelle
    *map_ptr = new_map;
    // Eski map dizisinin sadece pointer'ı serbest bırakılır, satırlar korunur
    free(map);
}

void get_map(t_cube *cube)
{
	int i;
	int j;
	int a;

	a = 0;
	i = 0;
	j = 0;
	while (!is_map_line(cube->all_of_file[i++]))
		j++;
	while (cube->all_of_file[i])
		i++;
	cube->map =	malloc(sizeof(char *) * (i - j + 1));
	if (!cube->map)
		put_error("Error: Memory allocation failed for map\n", cube);
	while (j < i)
	{
		cube->map[a++] = ft_strdup(cube->all_of_file[j]);
		j++;
	}
	cube->map[a] = NULL;
}

char **mapcpy(char **map, t_cube *cube)
{
	int	i;
	char **cpymap;
	i = 0;
	while (map[i] != NULL)
		i++;
	cpymap = malloc(sizeof(char *) * (i + 1));
	if (!cpymap)
		put_error("Error: Memory allocation failed for cpymap\n", cube);
	i = 0;
	while (map[i] != NULL)
	{
		cpymap[i] = ft_strdup(map[i]);
		i++;
	}
	cpymap[i] = NULL;
	return (cpymap);
}

void flood_fill(char **map, int x, int y, t_cube *cube)
{
	if (map[y][x] == ' ' || map[y][x] == '\t')
		put_error("Error: Invalid map", cube);
	if (map[y][x] == '1' || map[y][x] == 'X')
		return ;
	if (map[y][x] == '0' || map[y][x] == cube->player_pov)
		map[y][x] = 'X';
	if (map[y+1] && map[y+1][x])
		flood_fill(map, x + 1, y, cube);
	if (map[y-1] && map[y-1][x])
		flood_fill(map, x - 1, y, cube);
	if (map[y] && map[y][x+1])
		flood_fill(map, x, y + 1, cube);
	if (map[y] && map[y][x-1])
		flood_fill(map, x, y - 1, cube);
}

void add_space(char **map, int i, t_cube *cube)
{
    char *new_line;
    int len;
    int has_newline;

    len = strlen(map[i]);
    has_newline = ft_strchr_gnl(map[i], '\n');
    new_line = malloc(len + 3); // +2 space, +1 null
    if (!new_line)
        put_error("Error: Memory allocation failed\n", cube);
    new_line[0] = ' ';
    if (has_newline)
    {
        strncpy(new_line + 1, map[i], len - 1); // kopyala, \n hariç
        new_line[len] = ' ';
        new_line[len + 1] = '\n';
        new_line[len + 2] = '\0';
    }
    else
    {
        strcpy(new_line + 1, map[i]);
        new_line[len + 1] = ' ';
        new_line[len + 2] = '\0';
    }
    free(map[i]);
    map[i] = new_line;
}

void fill_space(char ***map, t_cube *cube)
{
    int i;
    int j;
    int max_length;
    char *line;
    char *newline_pos;

    max_length = find_largest_line(*map);
    i = 0;
    while ((*map)[i] != NULL)
    {
        line = (*map)[i];
        newline_pos = strchr(line, '\n');
        if (newline_pos)
            j = newline_pos - line;
        else
            j = strlen(line);

        while (j < max_length)
        {
            line[j] = ' ';
            j++;
        }
        if (newline_pos)
            line[j] = '\n';
        line[j + (newline_pos ? 1 : 0)] = '\0';
        i++;
    }
}

void manage_map(char ***map, t_cube *cube)
{
	int i;
	i = 0;
	while ((*map)[i] != NULL)
	{
		add_space(*map, i, cube);
		i++;
	}
	add_space_line(map, find_largest_line(*map), cube);
	fill_space(map, cube);
}

void check_double_map(char **map, t_cube *cube)
{
	int i;
	int j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (ft_strchr_gnl("01NSEW", map[i][j]) != 0)
				put_error("invalid map\n", cube);
			j++;
		}
		i++;
	}
}

void ffill(char **map, int x, int y, t_cube *cube)
{
    if (map[y][x] == 'X' || map[y][x] == ' ')
        return ;
    if (map[y][x] == '0' || map[y][x] == cube->player_pov || map[y][x] == '1')
        map[y][x] = 'X';
    if (map[y+1] && map[y+1][x])
        ffill(map, x + 1, y, cube);
    if (map[y-1] && map[y-1][x])
        ffill(map, x - 1, y, cube);
    if (map[y] && map[y][x+1])
        ffill(map, x, y + 1, cube);
    if (map[y] && map[y][x-1])
        ffill(map, x, y - 1, cube);
}

void check_map_chars(char **map, t_cube *cube)
{
	int i;
	int j;

	i = 0;
	while (map[i] != NULL)
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			if (ft_strchr_gnl("01NSEW\t\n ", map[i][j]) == 0)
			{
				fprintf(stderr, "Error: Invalid character '%c' in map\n", map[i][j]);
				end(cube, 1);
			}
			j++;
		}
		i++;
	}
}

void check_map(t_cube *cube)
{
	check_player(cube);
	check_map_chars(cube->map, cube);
	cube->cpymap=mapcpy(cube->map, cube);
	manage_map(&cube->cpymap, cube);
	cube->cpy_map=mapcpy(cube->cpymap, cube);
	int i = 0;
	flood_fill(cube->cpymap, cube->player_x + 1, cube->player_y + 1, cube);
	ffill(cube->cpy_map, cube->player_x + 1, cube->player_y + 1, cube);
	while (cube->cpy_map[i] != NULL)
	{
		printf("%s\n", cube->cpy_map[i]);
		i++;
	}
	check_double_map(cube->cpy_map, cube);
}