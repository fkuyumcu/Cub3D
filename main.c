/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalp <yalp@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 16:59:47 by yalp              #+#    #+#             */
/*   Updated: 2025/05/21 17:10:17 by yalp             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void arg_check(int argc, char **argv)
{
   
    
}

void init_cube(t_cube *cube)
{
    cube->width = 0;
    cube->height = 0;
    cube->map = NULL;
    cube->texture_n = NULL;
    cube->texture_s = NULL;
    cube->texture_e = NULL;
    cube->texture_w = NULL;
    cube->color_f = NULL;
    cube->color_c = NULL;
}
void map_check(t_cube *cube)
{
    
}

int main(int argc, char **argv)
{
    t_cube cube;

   
    arg_check(argc, argv);
    init_cube(&cube);
    map_check(&cube);
    // free resources
    return (0);
}