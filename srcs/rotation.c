/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 13:56:19 by jpfannku          #+#    #+#             */
/*   Updated: 2022/08/08 13:56:58 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

void	look_right(t_vars *vars)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = vars->player->dir_x;
	vars->player->dir_x = vars->player->dir_x * cos(0.05) \
		- vars->player->dir_y * sin(0.05);
	vars->player->dir_y = old_dir_x * sin(0.05) \
		+ vars->player->dir_y * cos(0.05);
	old_plane_x = vars->player->plane_x;
	vars->player->plane_x = vars->player->plane_x * cos(0.05) \
		- vars->player->plane_y * sin(0.05);
	vars->player->plane_y = old_plane_x * sin(0.05) + \
		vars->player->plane_y * cos(0.05);
}

void	look_left(t_vars *vars)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = vars->player->dir_x;
	vars->player->dir_x = vars->player->dir_x * \
		cos(-0.05) - vars->player->dir_y * sin(-0.05);
	vars->player->dir_y = old_dir_x * \
		sin(-0.05) + vars->player->dir_y * cos(-0.05);
	old_plane_x = vars->player->plane_x;
	vars->player->plane_x = vars->player->plane_x * \
		cos(-0.05) - vars->player->plane_y * sin(-0.05);
	vars->player->plane_y = old_plane_x * \
		sin(-0.05) + vars->player->plane_y * cos(-0.05);
}
