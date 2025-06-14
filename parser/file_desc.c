/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_desc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalp <yalp@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:31:37 by yalp              #+#    #+#             */
/*   Updated: 2025/06/14 15:52:38 by yalp             ###   ########.fr       */
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
	int	all_identifiers_collected;
	int	id;
	int	map_started;

	i = -1;
	all_identifiers_collected = 0;
	map_started = 0;
	while (cube->all_of_file[++i] != NULL)
	{
		if (is_empty_line(cube->all_of_file[i]))
			continue ;
		all_identifiers_collected = check_all_identifiers_collected(cube);
		id = is_ident_line(cube->all_of_file[i]);
		if (!all_identifiers_collected)
			handle_identifier_phase(cube, id, i);
		else
			handle_map_phase(cube, id, i, &map_started);
	}
	validate_identifiers_count(cube);
}
