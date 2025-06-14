/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_supply.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalp <yalp@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:49:38 by yalp              #+#    #+#             */
/*   Updated: 2025/06/14 15:52:54 by yalp             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

int	check_all_identifiers_collected(t_cube *cube)
{
	if (cube->count_n == 1 && cube->count_s == 1 && cube->count_e == 1
		&& cube->count_w == 1 && cube->count_f == 1 && cube->count_c == 1)
		return (1);
	return (0);
}

void	handle_identifier_phase(t_cube *cube, int id, int i)
{
	if (id)
		check_supply(cube, id, i);
	else
		put_error("Invalid line before all identifiers collected",
			cube->all_of_file[i], cube);
}

void	handle_map_phase(t_cube *cube, int id, int i, int *map_started)
{
	if (id)
		put_error("Identifier after all identifiers collected",
			cube->all_of_file[i], cube);
	else if (is_map_line(cube->all_of_file[i]))
		*map_started = 1;
	else if (*map_started)
		put_error("Invalid line in map", cube->all_of_file[i], cube);
	else
		put_error("Invalid line between identifiers and map",
			cube->all_of_file[i], cube);
}

void	validate_identifiers_count(t_cube *cube)
{
	if (cube->count_n != 1 || cube->count_s != 1 || cube->count_e != 1
		|| cube->count_w != 1 || cube->count_f != 1 || cube->count_c != 1)
		put_error("Missing identifiers in the file.", NULL, cube);
}
