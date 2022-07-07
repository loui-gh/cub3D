/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 20:51:36 by jpfannku          #+#    #+#             */
/*   Updated: 2022/07/07 20:51:39 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

int	mouse_click(t_vars *vars)
{
	ft_putstr("See you next time :)\n");
	mlx_destroy_window(vars->mlx_ptr, vars->mlx_win);
	exit(EXIT_SUCCESS);
	return (0);
}

int	esc(int keycode, t_vars *vars)
{
	if (keycode == 65307)
	{
		ft_putstr("See you next time ESC:)\n");
		mlx_destroy_window(vars->mlx_ptr, vars->mlx_win);
		exit(EXIT_SUCCESS);
	}
	return (0);
}
