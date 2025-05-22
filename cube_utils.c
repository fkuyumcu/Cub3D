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
        fprintf(stderr, "Error: Wrong number of arguments\n");
        exit(EXIT_FAILURE);
    }
    if (argv[1][strlen(argv[1]) - 4] != '.')
    {
        fprintf(stderr, "Error: Invalid file extension\n");
        exit(EXIT_FAILURE);
    }
    if (strcmp(&argv[1][strlen(argv[1]) - 4], ".cub") != 0)
    {
        fprintf(stderr, "Error: Invalid file extension\n");
        exit(EXIT_FAILURE);
    }
    if (open(argv[1], O_RDONLY) < 0)
    {
        fprintf(stderr, "Error: File can not be read\n");
        exit(EXIT_FAILURE);
    }
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
    cube->all_of_file = NULL;
    cube->player_pov = 0;
}


