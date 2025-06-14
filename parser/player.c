/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalp <yalp@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/13 16:05:12 by yalp              #+#    #+#             */
/*   Updated: 2025/06/14 15:43:35 by yalp             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	check_player_count_cube(t_cube *cube)
{
	if (cube->player_count == 0)
		put_error("No player in map", NULL, cube);
	if (cube->player_count > 1)
		put_error("Number of player more than 1", NULL, cube);
}
