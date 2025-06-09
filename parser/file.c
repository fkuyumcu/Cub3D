/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalp <yalp@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:32:00 by yalp              #+#    #+#             */
/*   Updated: 2025/06/04 15:02:20 by yalp             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

char	*skip_spaces(char *str)
{
	while (*str == ' ' || *str == '\t')
		str++;
	return (str);
}

char	*trim_spaces(char *str)
{
	char	*end;

	str = skip_spaces(str);
	if (*str == 0)
		return (str);
	end = str + ft_strlen(str) - 1;
	while (end > str && (*end == ' ' || *end == '\t' || *end == '\n'))
		end--;
	*(end + 1) = 0;
	return (str);
}

int	*init_values(char *color)
{
	char	**rgb;
	int		*values;
	int		i;

	rgb = ft_split(color, ',');
	if (!rgb)
		return (NULL);
	values = malloc(sizeof(int) * 3);
	if (!values)
	{
		free_double_pointer(rgb);
		return (NULL);
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

void	check_supply(t_cube *cube, int id, int i)
{
	char	*content;

	content = cube->all_of_file[i];
	if (id >= 1 && id <= 4 && !is_valid_path(content))
	{
		fprintf(stderr, "Invalid path for identifier: %s", cube->all_of_file[i]);
		end(cube, 1);
	}
	if ((id == 5 || id == 6) && !is_valid_rgb(content))
	{
		fprintf(stderr, "Invalid RGB value for identifier: %s", cube->all_of_file[i]);
		end(cube, 1);
	}
	send_to_init(cube, cube->all_of_file[i], id);
}

void	check_file(t_cube *cube)
{
	int	i;
	int	map_started;
	int	id;

	i = -1;
	map_started = 0;
	while (cube->all_of_file[++i] != NULL)
	{
		if (is_empty_line(cube->all_of_file[i]))
			continue;
		id = is_ident_line(cube->all_of_file[i]);
		if (!map_started && id)
			check_supply(cube, id, i);
		else if (is_map_line(cube->all_of_file[i]))
			map_started = 1;
		else if (map_started && id)
			put_error("Identifier after map started", NULL, cube);
		else if (!map_started && !id)
			put_error("Invalid identifier or map line", NULL, cube);
	}
	if (cube->count_n != 1 || cube->count_s != 1 || cube->count_e != 1
		|| cube->count_w != 1 || cube->count_f != 1 || cube->count_c != 1)
		put_error("Missing or duplicate identifiers in the file.", NULL, cube);
}


// Satır tamamen boş mu kontrolü
int	is_empty_line(char *line)
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
int	is_valid_path(char *line)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (*line == '\0' || *line == '\n')
		return (0);
	return (1);
}

void	init_idents(t_cube *cube, char *line, int id)
{
	char	*value;

	value = trim_spaces(line);
	if (id == 1)
	cube->texture_n = ft_strdup(skip_spaces(value + 2));
	else if (id == 2)
	cube->texture_s = ft_strdup(skip_spaces(value + 2));
	else if (id == 3)
	cube->texture_e = ft_strdup(skip_spaces(value + 2));
	else if (id == 4)
	cube->texture_w = ft_strdup(skip_spaces(value + 2));
	else if (id == 5)
	{
		cube->color_f = ft_strdup(skip_spaces(value + 1));
		cube->values_f = init_values(cube->color_f);
	}
	else if (id == 6)
	{
		cube->color_c = ft_strdup(skip_spaces(value + 1));
		cube->values_c = init_values(cube->color_c);
	}
	else
		return;
}

void	send_to_init(t_cube *cube, char *line, int id)
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

int	is_ident_line(char *line)
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

void	read_file(t_cube *cube, char *file)
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
	while (y-- > 0)
		cube->all_of_file[i++] = get_next_line(fd);
	free(cube->all_of_file[i]);
	cube->all_of_file[i] = NULL;
	close(fd);
}
