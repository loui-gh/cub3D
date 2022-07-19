/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 20:51:36 by jpfannku          #+#    #+#             */
/*   Updated: 2022/07/19 11:04:58 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

int	mouse_click(t_vars *vars)
{
	//mlx_destroy_image(vars->mlx_ptr, vars->img); //why does this segfault?
	mlx_destroy_window(vars->mlx_ptr, vars->mlx_win);
	free_vars_exit("See you next time :)\n", vars, EXIT_SUCCESS);
	return (0);
}

int	esc(int keycode, t_vars *vars)
{
	if (keycode == 65307)
	{
		//mlx_destroy_image(vars->mlx_ptr, vars->img);
		mlx_destroy_window(vars->mlx_ptr, vars->mlx_win);
		free_vars_exit("See you next time :)\n", vars, EXIT_SUCCESS);
	}
	return (0);
}
