/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalp <yalp@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:31:28 by yalp              #+#    #+#             */
/*   Updated: 2025/06/02 17:20:12 by yalp             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void free_double_pointer(char **ptr)
{
	int i = 0;
	if (!ptr)
		return;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void end(t_cube *cube, int exit_code)
{
	if (cube->all_of_file != NULL)
		free_double_pointer(cube->all_of_file);
	if (cube->map != NULL)
		free_double_pointer(cube->map);
	if (cube->cpymap != NULL)
		free_double_pointer(cube->cpymap);
	if (cube->cpy_map != NULL)
		free_double_pointer(cube->cpy_map);
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
	exit(exit_code);
}
