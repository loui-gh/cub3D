/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/08 13:53:50 by jpfannku          #+#    #+#             */
/*   Updated: 2022/08/09 11:12:52 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

void	move_backward(t_vars *vars)
{
	if (vars->map->map_arr[(int)vars->player->pos_y][(int) \
		(vars->player->pos_x - vars->player->dir_x * 0.2)] != '1')
		vars->player->pos_x -= vars->player->dir_x * 0.2;
	if (vars->map->map_arr[(int)(vars->player->pos_y - vars->player->dir_y \
		* 0.2)][(int)(vars->player->pos_x)] != '1')
		vars->player->pos_y -= vars->player->dir_y * 0.2;
}

void	move_forward(t_vars *vars)
{
	if (vars->map->map_arr[(int)vars->player->pos_y][(int) \
		(vars->player->pos_x + vars->player->dir_x * 0.2)] != '1')
		vars->player->pos_x += vars->player->dir_x * 0.2;
	if (vars->map->map_arr[(int)(vars->player->pos_y + vars->player->dir_y \
		* 0.2)][(int)(vars->player->pos_x)] != '1')
		vars->player->pos_y += vars->player->dir_y * 0.2;
}

void	move_left(t_vars *vars)
{
	if (vars->map->map_arr[(int)vars->player->pos_y][(int) \
		(vars->player->pos_x - vars->player->plane_x * 0.2)] != '1')
		vars->player->pos_x -= vars->player->plane_x * 0.2;
	if (vars->map->map_arr[(int)(vars->player->pos_y - \
		vars->player->plane_y * 0.2)][(int)(vars->player->pos_x)] != '1')
		vars->player->pos_y -= vars->player->plane_y * 0.2;
}

void	move_right(t_vars *vars)
{
	if (vars->map->map_arr[(int)vars->player->pos_y][(int) \
		(vars->player->pos_x + vars->player->plane_x * 0.2)] != '1')
		vars->player->pos_x += vars->player->plane_x * 0.2;
	if (vars->map->map_arr[(int)(vars->player->pos_y + \
		vars->player->plane_y * 0.2)][(int)(vars->player->pos_x)] != '1')
		vars->player->pos_y += vars->player->plane_y * 0.2;
}

int	player_move(int keycode, t_vars *vars)
{
	if (keycode == W_KEY)
		move_forward(vars);
	if (keycode == S_KEY)
		move_backward(vars);
	if (keycode == A_KEY)
		move_left(vars);
	if (keycode == D_KEY)
		move_right(vars);
	if (keycode == LEFT_KEY)
		look_left(vars);
	if (keycode == RIGHT_KEY)
		look_right(vars);
	return (0);
}
