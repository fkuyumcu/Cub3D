/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalp <yalp@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 15:32:07 by fkuyumcu          #+#    #+#             */
/*   Updated: 2025/06/11 14:34:27 by yalp             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	check_textures(t_cube *cube)
{
	if (open(cube->texture_e, O_RDONLY) == -1)
		put_error("Loading Texture", NULL, cube);
	if (open(cube->texture_w, O_RDONLY) == -1)
		put_error("Loading Texture", NULL, cube);
	if (open(cube->texture_s, O_RDONLY) == -1)
		put_error("Loading Texture", NULL, cube);
	if (open(cube->texture_n, O_RDONLY) == -1)
		put_error("Loading texture.", NULL, cube);
}

void	get_addr(t_cube *cube)
{
	cube->e_text.data = (int *)mlx_get_data_addr(cube->e_text.img,
			&cube->e_text.bpp, &cube->e_text.line_length, &cube->e_text.endian);
	cube->w_text.data = (int *)mlx_get_data_addr(cube->w_text.img,
			&cube->w_text.bpp, &cube->w_text.line_length, &cube->w_text.endian);
	cube->n_text.data = (int *)mlx_get_data_addr(cube->n_text.img,
			&cube->n_text.bpp, &cube->n_text.line_length, &cube->n_text.endian);
	cube->s_text.data = (int *)mlx_get_data_addr(cube->s_text.img,
			&cube->s_text.bpp, &cube->s_text.line_length, &cube->s_text.endian);
}

void error_hook(t_cube *cube)
{
	ft_putstr_fd("Error: Broken XPM\n", 2);
	close_hook(cube);
}

void	load_textures(t_cube *cube)
{
	int	width;
	int	height;

	cube->e_text.img = mlx_xpm_file_to_image(cube->mlx, cube->texture_e, &width,
			&height);
	cube->e_text.width = width;
	cube->e_text.height = height;
	cube->w_text.img = mlx_xpm_file_to_image(cube->mlx, cube->texture_w, &width,
			&height);
	cube->w_text.width = width;
	cube->w_text.height = height;
	cube->n_text.img = mlx_xpm_file_to_image(cube->mlx, cube->texture_n, &width,
			&height);
	cube->n_text.width = width;
	cube->n_text.height = height;
	cube->s_text.img = mlx_xpm_file_to_image(cube->mlx, cube->texture_s, &width,
			&height);
	cube->s_text.width = width;
	cube->s_text.height = height;
	if(!(cube->e_text.img && cube->w_text.img
		&& cube->n_text.img && cube->s_text.img))
		error_hook(cube);
	get_addr(cube);
}
