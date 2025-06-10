/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalp <yalp@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/01 14:54:32 by yalp              #+#    #+#             */
/*   Updated: 2025/06/01 14:54:40 by yalp             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int main(int argc, char **argv)
{
	t_cube cube;

	arg_check(argc, argv);
	init_cube(&cube);
	read_file(&cube, argv[1]);
	check_file(&cube);
	get_map(&cube);
	check_map(&cube);
	check_player(&cube);

	// Here you would typically initialize the graphics library and start the game loop.
	// For example:
	// mlx_init(&cube);
	// mlx_loop(&cube);

	end(&cube, 0); // Clean up and exit
	return 0;
}