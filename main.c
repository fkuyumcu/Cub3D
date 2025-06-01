/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:59:47 by yalp              #+#    #+#             */
/*   Updated: 2025/05/31 16:59:15 by fkuyumcu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"


void draw_square(int x, int y, int size, int color, t_cube *game)
{

    for (int i = 0; i < size; i++)
        put_pixel(x + i, y, color, game);
    for (int i = 0; i < size; i++)
        put_pixel(x, y + i, color, game);
    for (int i = 0; i < size; i++)
        put_pixel(x + size, y + i, color, game);
    for (int i = 0; i < size; i++)
        put_pixel(x + i, y + size, color, game);
}


int main(int argc, char **argv)
{
    t_cube cube;

    parser(argc, argv, &cube);
    init_mlx(&cube);
    init_player(&cube); // Bu satırı ekliyoruz!
    
    cube.player.x = (cube.player_x * BLOCK_SIZE) + (BLOCK_SIZE / 2);
    cube.player.y = (cube.player_y * BLOCK_SIZE) + (BLOCK_SIZE / 2);
    
    if (cube.player_pov == 'N')
        cube.player.angle = 3 * PI / 2;  
    else if (cube.player_pov == 'S')
        cube.player.angle = PI / 2;      // South (down)
    else if (cube.player_pov == 'E')
        cube.player.angle = 0;           // East (right)
    else if (cube.player_pov == 'W')
        cube.player.angle = PI;          // West (left)
    
    // Load textures using MLX
    int width, height;
    cube.e_text.img = mlx_xpm_file_to_image(cube.mlx, cube.texture_e, &width, &height);
    cube.e_text.width = width;
    cube.e_text.height = height;
    
    cube.w_text.img = mlx_xpm_file_to_image(cube.mlx, cube.texture_w, &width, &height);
    cube.w_text.width = width;
    cube.w_text.height = height;
    
    cube.n_text.img = mlx_xpm_file_to_image(cube.mlx, cube.texture_n, &width, &height);
    cube.n_text.width = width;
    cube.n_text.height = height;
    
    cube.s_text.img = mlx_xpm_file_to_image(cube.mlx, cube.texture_s, &width, &height);
    cube.s_text.width = width;
    cube.s_text.height = height;
    
    if (!cube.e_text.img || !cube.w_text.img || !cube.n_text.img || !cube.s_text.img)
    {
        fprintf(stderr, "Error: Failed to load textures\n");
        return (1);
    }
    
    cube.e_text.data = (int *)mlx_get_data_addr(cube.e_text.img, &cube.e_text.bpp, &cube.e_text.line_length, &cube.e_text.endian);
    cube.w_text.data = (int *)mlx_get_data_addr(cube.w_text.img, &cube.w_text.bpp, &cube.w_text.line_length, &cube.w_text.endian);
    cube.n_text.data = (int *)mlx_get_data_addr(cube.n_text.img, &cube.n_text.bpp, &cube.n_text.line_length, &cube.n_text.endian);
    cube.s_text.data = (int *)mlx_get_data_addr(cube.s_text.img, &cube.s_text.bpp, &cube.s_text.line_length, &cube.s_text.endian);

    mlx_hook(cube.win, 2, 1, key_press_hook, &cube);   // 1L<<0 eventler ve maskler??
    mlx_hook(cube.win, 3, 2, key_release_hook, &cube); // 1L<<1
    mlx_loop_hook(cube.mlx, loop_hook, &cube);

    mlx_loop(cube.mlx);
    return (0);
}