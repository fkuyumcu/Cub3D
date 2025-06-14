/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filling.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalp <yalp@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:59:05 by yalp              #+#    #+#             */
/*   Updated: 2025/06/12 13:49:06 by yalp             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	ft_isdigit(int c)
{
	if (c <= 57 && c >= 48)
		return (1);
	else
		return (0);
}

void	check_rgb_values(char **rgb, t_cube *cube)
{
	int	i;
	int	j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (rgb[i][j])
		{
			if (rgb[i][0] == '0' && ft_strlen(rgb[i]) != 1)
			{
				free_double_pointer(rgb);
				put_error("Invalid rgb", NULL, cube);
			}
			if (ft_isdigit(rgb[i][j]) == 0)
			{
				free_double_pointer(rgb);
				put_error("Invalid rgb", NULL, cube);
			}
			j++;
		}
		i++;
	}
}

void	check_rgb(char **rgb, char *line, t_cube *cube)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i++] == ',')
			count++;
	}
	if (count > 2)
	{
		free_double_pointer(rgb);
		put_error("Invalid rgb", NULL, cube);
	}
}

char	*make_filled_line(char *line, int old_len, int max_length)
{
	char	*new_line;
	int		j;
	char	*newline_pos;

	newline_pos = ft_strchr(line, '\n');
	new_line = malloc(max_length + 2);
	if (!new_line)
		return (NULL);
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
	return (new_line);
}

void	fill_space(char ***map)
{
	int		i;
	int		max_length;
	int		old_len;
	char	*newline_pos;
	char	*new_line;

	max_length = find_largest_line(*map);
	i = 0;
	while ((*map)[i])
	{
		newline_pos = ft_strchr((*map)[i], '\n');
		if (newline_pos)
			old_len = newline_pos - (*map)[i];
		else
			old_len = ft_strlen((*map)[i]);
		if (old_len < max_length)
		{
			new_line = make_filled_line((*map)[i], old_len, max_length);
			if (!new_line)
				return ;
			free((*map)[i]);
			(*map)[i] = new_line;
		}
		i++;
	}
}
