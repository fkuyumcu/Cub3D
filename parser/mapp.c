/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalp <yalp@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:37:12 by yalp              #+#    #+#             */
/*   Updated: 2025/06/10 15:38:51 by yalp             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	find_largest_line(char **map)
{
	int	i;
	int	max_length;
	int	length;

	i = 0;
	max_length = 0;
	while (map[i] != NULL)
	{
		length = ft_strlen(map[i]);
		if (length > max_length)
			max_length = length;
		i++;
	}
	return (max_length);
}

void	add_space_line(char ***map_ptr, int space_count, t_cube *cube)
{
	int		i;
	int		old_len;
	char	**map;
	char	**new_map;
	char	*space_line;

	i = -1;
	old_len = 0;
	map = *map_ptr;
	while (map[old_len])
		old_len++;
	new_map = malloc(sizeof(char *) * (old_len + 3));
	if (!new_map)
		put_error("Memory allocation failed", NULL, cube);
	space_line = malloc(space_count + 2);
	if (!space_line)
		put_error("Memory allocation failed", NULL, cube);
	ft_memset(space_line, ' ', space_count);
	space_line[space_count] = '\n';
	space_line[space_count + 1] = '\0';
	new_map[0] = space_line;
	while (++i < old_len)
		new_map[i + 1] = map[i];
	space_line = malloc(space_count + 2);
	if (!space_line)
		put_error("Memory allocation failed", NULL, cube);
	ft_memset(space_line, ' ', space_count);
	space_line[space_count] = '\n';
	space_line[space_count + 1] = '\0';
	new_map[old_len + 1] = space_line;
	new_map[old_len + 2] = NULL;
	*map_ptr = new_map;
	free(map);
}

void	add_space(char **map, int i, t_cube *cube)
{
	char	*new_line;
	int		len;
	char	*has_newline;

	len = ft_strlen(map[i]);
	has_newline = ft_strchr(map[i], '\n');
	new_line = malloc(len + 3);
	if (!new_line)
		put_error("Memory allocation failed", NULL, cube);
	new_line[0] = ' ';
	if (has_newline)
	{
		ft_strncpy(new_line + 1, map[i], len - 1);
		new_line[len] = ' ';
		new_line[len + 1] = '\n';
		new_line[len + 2] = '\0';
	}
	else
	{
		ft_strcpy(new_line + 1, map[i]);
		new_line[len + 1] = ' ';
		new_line[len + 2] = '\0';
	}
	free(map[i]);
	map[i] = new_line;
}

void	fill_space(char ***map)
{
	int		i;
	int		j;
	int		max_length;
	char	*line;
	char	*newline_pos;
	char	*new_line;
	int		old_len;

	max_length = find_largest_line(*map);
	i = 0;
	while ((*map)[i] != NULL)
	{
		line = (*map)[i];
		newline_pos = ft_strchr(line, '\n');
		if (newline_pos)
			old_len = newline_pos - line;
		else
			old_len = ft_strlen(line);
		if (old_len < max_length)
		{
			new_line = malloc(max_length + 2);
			if (!new_line)
				return ;
			ft_strncpy(new_line, line, old_len);
			j = old_len;
			while (j < max_length)
				new_line[j++] = ' ';
			if (newline_pos)
			{
				new_line[j] = '\n';
				new_line[j + 1] = '\0';
			}
			else
				new_line[j] = '\0';
			free((*map)[i]);
			(*map)[i] = new_line;
		}
		i++;
	}
}

void	manage_map(char ***map, t_cube *cube)
{
	int	i;

	i = 0;
	while ((*map)[i] != NULL)
	{
		add_space(*map, i, cube);
		i++;
	}
	add_space_line(map, find_largest_line(*map), cube);
	fill_space(map);
}
