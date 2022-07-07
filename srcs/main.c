/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 15:07:34 by jpfannku          #+#    #+#             */
/*   Updated: 2022/07/07 17:21:34 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

int	main(int argc, char **argv)
{
	t_vars		vars;
	int			fd;

	if (argc != 2)
		exit_msg("enter cmd like this --> ./cub3D *.cub\n");
	check_file_ext(argv[1]);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		exit_msg("Cannot read from file\n");
	vars.tex = init_textures(fd); //check when invalid textures or rgb codes. 
	vars.map = create_map_array(fd);
	//printf("colour: %x\n", vars.tex->floor);
	//print_arr(vars.map->map_arr);
	check_map(vars.map->map_arr, &vars);
	vars.mlx_ptr = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx_ptr, 640, 480, "Hello world!");
	raycast(&vars);
	mlx_hook(vars.mlx_win, 2, 27, esc, &vars);
	mlx_hook(vars.mlx_win, 17, (1L << 17), mouse_click, &vars); //free inside function
	mlx_loop(vars.mlx_ptr);
}
