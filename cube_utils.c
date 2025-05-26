/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkuyumcu <fkuyumcu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 12:54:57 by fkuyumcu          #+#    #+#             */
/*   Updated: 2025/05/26 13:12:40 by fkuyumcu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

void end(t_cube *cube)
{
    int i = 0;
    while (cube->all_of_file && cube->all_of_file[i])
    {
        if (cube->all_of_file[i] != NULL)
            free(cube->all_of_file[i]);
        i++;
    }
    if (cube->all_of_file != NULL)
        free(cube->all_of_file);
    exit(EXIT_FAILURE);
}

void arg_check(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Error: Wrong number of arguments\n");//fprintf
        exit(EXIT_FAILURE);
    }
    if (argv[1][strlen(argv[1]) - 4] != '.')
    {
        fprintf(stderr, "Error: Invalid file extension\n");//fprintf
        exit(EXIT_FAILURE);
    }
    if (strcmp(&argv[1][strlen(argv[1]) - 4], ".cub") != 0)//fprintf
    {
        fprintf(stderr, "Error: Invalid file extension\n");
        exit(EXIT_FAILURE);
    }
    if (open(argv[1], O_RDONLY) < 0)
    {
        fprintf(stderr, "Error: File can not be read\n");//fprintf
        exit(EXIT_FAILURE);
    }
}




