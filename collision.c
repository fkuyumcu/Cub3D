/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 15:20:24 by fkuyumcu          #+#    #+#             */
/*   Updated: 2025/05/26 15:20:24 by fkuyumcu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

bool is_colliding_point(float ray_x, float ray_y, t_cube *cub)
{
    int x;
    int y;

    x = ray_x / BLOCK_SIZE;
    y = ray_y / BLOCK_SIZE;
    
    if (x < 0 || y < 0 || !cub->map[y] || cub->map[y][x] == '\0')
        return (true);
    
    if (cub->map[y][x] == '1')
        return (true);
    return (false);
}

bool is_colliding(float ray_x, float ray_y, t_cube *cub)
{
    float player_radius = BLOCK_SIZE / 15.0;
    
    if (is_colliding_point(ray_x, ray_y, cub))
        return (true);
    
    if (is_colliding_point(ray_x + player_radius, ray_y + player_radius, cub))
        return (true);
    if (is_colliding_point(ray_x + player_radius, ray_y - player_radius, cub))
        return (true);
    if (is_colliding_point(ray_x - player_radius, ray_y + player_radius, cub))
        return (true);
    if (is_colliding_point(ray_x - player_radius, ray_y - player_radius, cub))
        return (true);
    
    return (false);
}
