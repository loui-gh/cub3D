/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 20:51:36 by jpfannku          #+#    #+#             */
/*   Updated: 2022/08/08 10:57:42 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

int	mouse_click(t_vars *vars)
{
	vars->finished = 1;
	mlx_destroy_window(vars->mlx_ptr, vars->mlx_win);
	free_vars_exit("See you next time :)\n", vars, EXIT_SUCCESS);
	return (0);
}

int	esc(int keycode, t_vars *vars)
{
	if (keycode == ESC_KEY)
	{
		vars->finished = 1;
		mlx_destroy_window(vars->mlx_ptr, vars->mlx_win);
		free_vars_exit("See you next time :)\n", vars, EXIT_SUCCESS);
	}
	return (0);
}
