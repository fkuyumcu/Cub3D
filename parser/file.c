/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalp <yalp@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:32:00 by yalp              #+#    #+#             */
/*   Updated: 2025/06/10 15:33:13 by yalp             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

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
		return ;
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
	while (*line == ' ' || *line == '\t')
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
	cube->all_of_file[i] = NULL;
	close(fd);
}
