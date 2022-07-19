/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 15:07:34 by jpfannku          #+#    #+#             */
/*   Updated: 2022/07/19 21:02:54 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

t_vars	*init_game(int fd)
{
	t_vars	*vars;

	vars = (t_vars *)ft_calloc(sizeof(t_vars), 1);
	vars->mlx_ptr = mlx_init(); //this causes a huge memory leak??
	if (vars->mlx_ptr == NULL)
		exit_msg("Error: Failed to init MLX\n", EXIT_FAILURE);
	init_textures(fd, vars);
	create_map_array(fd, vars); //found a problem when removing a single wall from the right side of the map.
	return (vars);
}

int	main(int argc, char **argv)
{
	t_vars		*vars;
	int			fd;

	if (argc != 2)
		exit_msg("enter cmd like this --> ./cub3D *.cub\n", EXIT_FAILURE);
	check_file_ext(argv[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit_msg("Cannot read from file\n", EXIT_FAILURE);
	vars = init_game(fd);
	vars->mlx_win = mlx_new_window(vars->mlx_ptr, 640, 480, "Hello world!");
	//raycast(&vars);
	raycast_tex(vars);
	mlx_hook(vars->mlx_win, 2, 27, esc, vars);
	mlx_hook(vars->mlx_win, 17, (1L << 17), mouse_click, vars);
	mlx_loop(vars->mlx_ptr);
}
