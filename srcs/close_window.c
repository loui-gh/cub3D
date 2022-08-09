/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_window.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 12:15:59 by jpfannku          #+#    #+#             */
/*   Updated: 2022/08/09 20:11:26 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

int	mouse_click(t_vars *vars)
{
	mlx_destroy_window(vars->mlx_ptr, vars->mlx_win);
	free_vars_exit("See you next time :)\n", vars, EXIT_SUCCESS);
	return (0);
}

int	esc(int keycode, t_vars *vars)
{
	if (keycode == ESC_KEY)
	{
		mlx_destroy_window(vars->mlx_ptr, vars->mlx_win);
		free_vars_exit("See you next time :)\n", vars, EXIT_SUCCESS);
	}
	return (0);
}

#if __linux__

void	kill_disp(t_vars *vars)
{
	if (vars->mlx_ptr)
	{
		mlx_loop_end(vars->mlx_ptr);
		mlx_destroy_display(vars->mlx_ptr);
		free(vars->mlx_ptr);
	}
}

#else

void	kill_disp(t_vars *vars)
{
	(void) vars;
}

#endif
