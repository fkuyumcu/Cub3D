/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 13:08:26 by fkuyumcu          #+#    #+#             */
/*   Updated: 2025/06/02 15:56:20 by fkuyumcu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void init_mlx(t_cube *cube)
{
    cube->mlx = mlx_init();
    cube->win = mlx_new_window(cube->mlx, WIDTH, HEIGHT, "Cub3D");
    cube->img = mlx_new_image(cube->mlx, WIDTH, HEIGHT);
    mlx_put_image_to_window(cube->mlx, cube->win, cube->img, 0, 0);
    cube->data = mlx_get_data_addr(cube->img, &cube->bpp, &cube->size_line, &cube->endian);
}

void clear_image(t_cube *cube)
{
    int x;
    int y;

    y = 0;
    while(y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            put_pixel(x, y, 0, cube);
            x++;
        }
        y++;
    }
}




