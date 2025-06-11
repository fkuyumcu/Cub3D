/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:59:47 by yalp              #+#    #+#             */
/*   Updated: 2025/06/11 13:21:38 by fkuyumcu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	draw_square(int x, int y, int size, t_cube *game)
{
	int	i;

	i = -1;
	while (++i < size)
		put_pixel(x + i, y, 0xFF0000, game);
	i = -1;
	while (++i < size)
		put_pixel(x, y + i, 0xFF0000, game);
	i = -1;
	while (++i < size)
		put_pixel(x + size, y + i, 0xFF0000, game);
	i = -1;
	while (++i < size)
		put_pixel(x + i, y + size, 0xFF0000, game);
}

int	close_hook(t_cube *cube)
{
	if (cube->img)
		mlx_destroy_image(cube->mlx, cube->img);
	if (cube->e_text.img)
		mlx_destroy_image(cube->mlx, cube->e_text.img);
	if (cube->w_text.img)
		mlx_destroy_image(cube->mlx, cube->w_text.img);
	if (cube->n_text.img)
		mlx_destroy_image(cube->mlx, cube->n_text.img);
	if (cube->s_text.img)
		mlx_destroy_image(cube->mlx, cube->s_text.img);
	if (cube->win)
		mlx_destroy_window(cube->mlx, cube->win);
	if (cube->mlx)
	{
		mlx_destroy_display(cube->mlx);
		free(cube->mlx);
	}
	end (cube, 0);
	return (0);
}

void	set_direction(t_cube *cub)
{
	cub->player.x = (cub->player_x * BLOCK_SIZE) + (BLOCK_SIZE / 2);
	cub->player.y = (cub->player_y * BLOCK_SIZE) + (BLOCK_SIZE / 2);
	if (cub->player_pov == 'N')
		cub->player.angle = 3 * PI / 2;
	else if (cub->player_pov == 'S')
		cub->player.angle = PI / 2;
	else if (cub->player_pov == 'E')
		cub->player.angle = 0;
	else if (cub->player_pov == 'W')
		cub->player.angle = PI;
}

int	main(int argc, char **argv)
{
	t_cube	cube;

	parser(argc, argv, &cube);
	check_textures(&cube);
	init_mlx(&cube);
	init_player(&cube);
	set_direction(&cube);
	load_textures(&cube);
	mlx_hook(cube.win, 2, 1, key_press_hook, &cube);
	mlx_hook(cube.win, 3, 2, key_release_hook, &cube);
	mlx_hook(cube.win, 17, 0, close_hook, &cube);
	mlx_loop_hook(cube.mlx, loop_hook, &cube);
	mlx_loop(cube.mlx);
	return (0);
}
