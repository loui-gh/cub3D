/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 15:07:34 by jpfannku          #+#    #+#             */
/*   Updated: 2022/08/11 21:22:28 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

/*Assigns the main variable struct, which contains the mlx pointers and 
pointers to all other structs. Also calls init functions for the 
map and textures.*/

void	init_img(t_vars *vars)
{
	vars->img = (t_data *)malloc(sizeof(t_data));
	vars->img->img = mlx_new_image(vars->mlx_ptr, WIDTH, HEIGHT);
	vars->img->addr = mlx_get_data_addr(vars->img->img, \
					&vars->img->bits_per_pixel, \
					&vars->img->line_length, &vars->img->endian);
}

t_vars	*init_game(int fd)
{
	t_vars	*vars;

	vars = (t_vars *)ft_calloc(sizeof(t_vars), 1);
	if (!vars)
	{
		close(fd);
		exit_msg("Error: Malloc error\n", EXIT_FAILURE);
	}
	vars->mlx_ptr = mlx_init();
	if (vars->mlx_ptr == NULL)
	{
		close(fd);
		exit_msg("Error: Failed to init MLX\n", EXIT_FAILURE);
	}
	init_textures(fd, vars);
	create_map_array(fd, vars);
	init_img(vars);
	vars->ray = (t_raycast *)ft_calloc(sizeof(t_raycast), 1);
	return (vars);
}

int	main(int argc, char **argv)
{
	t_vars		*vars;
	int			fd;

	if (argc != 2)
		exit_msg("enter cmd like this --> ./cub3D maps/*.cub\n", EXIT_FAILURE);
	if (check_file_ext(argv[1], ".cub") < 0)
		exit_msg("Wrong file extention mate ;) \n", EXIT_FAILURE);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit_msg("Cannot read from file\n", EXIT_FAILURE);
	vars = init_game(fd);
	vars->mlx_win = mlx_new_window(vars->mlx_ptr, WIDTH, HEIGHT, "Cub3D");
	mlx_loop_hook(vars->mlx_ptr, &render_image, vars);
	mlx_key_hook(vars->mlx_win, player_move, vars);
	mlx_hook(vars->mlx_win, 2, 27, esc, vars);
	mlx_hook(vars->mlx_win, 17, (1L << 17), mouse_click, vars);
	mlx_loop(vars->mlx_ptr);
}
