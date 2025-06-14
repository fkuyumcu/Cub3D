/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalp <yalp@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 15:31:28 by yalp              #+#    #+#             */
/*   Updated: 2025/06/14 15:08:34 by yalp             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cube.h"

void	put_error(char *message, char *messagee, t_cube *cube)
{
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(message, 2);
	if (messagee != NULL)
	{
		ft_putstr_fd(" ", 2);
		ft_putstr_fd(messagee, 2);
	}
	ft_putstr_fd("\n", 2);
	end(cube, 1);
}

void	arg_check(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_putstr_fd("Error: Wrong number of arguments\n", 2);
		exit(EXIT_FAILURE);
	}
	if (argv[1][ft_strlen(argv[1]) - 4] != '.' || ft_strlen(argv[1]) < 5)
	{
		ft_putstr_fd("Error: Invalid file extension\n", 2);
		exit(EXIT_FAILURE);
	}
	if (ft_strcmp(&argv[1][ft_strlen(argv[1]) - 4], ".cub") != 0)
	{
		ft_putstr_fd("Error: Invalid file extension\n", 2);
		exit(EXIT_FAILURE);
	}
	if (open(argv[1], O_RDONLY) < 0)
	{
		ft_putstr_fd("Error: File can not be read\n", 2);
		exit(EXIT_FAILURE);
	}
}

int	is_empty_line(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line != '\n')
			return (0);
		line++;
	}
	return (1);
}

void	free_double_pointer(char **ptr)
{
	int	i;

	i = 0;
	if (!ptr)
		return ;
	while (ptr[i])
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

void	end(t_cube *cube, int exit_code)
{
	if (cube->all_of_file != NULL)
		free_double_pointer(cube->all_of_file);
	if (cube->map != NULL)
		free_double_pointer(cube->map);
	if (cube->cpymap != NULL)
		free_double_pointer(cube->cpymap);
	if (cube->cpy_map != NULL)
		free_double_pointer(cube->cpy_map);
	if (cube->texture_n != NULL)
		free(cube->texture_n);
	if (cube->texture_s != NULL)
		free(cube->texture_s);
	if (cube->texture_e != NULL)
		free(cube->texture_e);
	if (cube->texture_w != NULL)
		free(cube->texture_w);
	if (cube->color_f != NULL)
		free(cube->color_f);
	if (cube->color_c != NULL)
		free(cube->color_c);
	if (cube->values_c != NULL)
		free(cube->values_c);
	if (cube->values_f != NULL)
		free(cube->values_f);
	exit(exit_code);
}
