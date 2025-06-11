/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_desc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalp <yalp@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:31:37 by yalp              #+#    #+#             */
/*   Updated: 2025/06/11 15:47:31 by yalp             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

char	*skip_spaces(char *str)
{
	while (*str == ' ')
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
	while (end > str && (*end == ' ' || *end == '\n'))
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
	if (id >= 1 && id <= 4
		&& !is_valid_path(skip_spaces(trim_spaces(content) + 2)))
		put_error("Invalid path for identifier:", cube->all_of_file[i], cube);
	if ((id == 5 || id == 6) && !is_valid_rgb(content, cube))
		put_error("Invalid RGB value for identifier:", cube->all_of_file[i],
			cube);
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
			continue ;
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
		put_error("Missing identifiers in the file.", NULL, cube);
}
