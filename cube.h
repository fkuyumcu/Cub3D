/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalp <yalp@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/21 17:02:34 by yalp              #+#    #+#             */
/*   Updated: 2025/05/22 16:33:56 by yalp             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include "minilibx-linux/mlx.h"
# include "get_next_line.h"

typedef struct s_cube
{
	char	**all_of_file;
	char	**map;
	char	*texture_s;
	int		count_s;
	char	*texture_n;
	int		count_n;
	char	*texture_w;
	int		count_w;
	char	*texture_e;
	int		count_e;
	char	*color_c;
	int		count_c;
	char	*color_f;
	int		count_f;
	char	player_pov;
	int		width;
	int		height;
	void	*mlx;
	void	*win;
}	t_cube;

#endif