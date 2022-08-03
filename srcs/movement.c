/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 13:50:21 by jpfannku          #+#    #+#             */
/*   Updated: 2022/08/03 23:48:37 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

// int	go_west(t_vars *vars, t_map *map, t_player *player)
// {
// 	if (map->map_arr[(int)vars->player->pos_y][(int)player->pos_x - 1] == '1')
// 		return (0);
// 	player->pos_x -= 0.2;
// 	return (0);
// }

// int	go_east(t_vars *vars, t_map *map, t_player *player)
// {
// 	if (map->map_arr[(int)vars->player->pos_y][(int)player->pos_x + 1] == '1')
// 		return (0);
// 	player->pos_x += 0.2;
// 	return (0);
// }

// int	go_north(t_vars *vars, t_map *map, t_player *player)
// {
// 	if (map->map_arr[(int)vars->player->pos_y - 1][(int)player->pos_x] == '1')
// 		return (0);
// 	player->pos_y -= 0.2;
// 	return (0);
// }

// int	go_south(t_vars *vars, t_map *map, t_player *player)
// {
// 	if (map->map_arr[(int)vars->player->pos_y + 1][(int)player->pos_x] == '1')
// 		return (0);
// 	player->pos_y += 0.2;
// 	return (0);
// }

void	look_left(t_vars *vars)
{
	//both camera direction and camera plane must be rotated
      double old_dir_x;
	  double old_plane_x;
	
	  old_dir_x = vars->player->dir_x;
	  vars->player->dir_x = vars->player->dir_x * cos(-0.05) - vars->player->dir_y * sin(-0.05);
      vars->player->dir_y = old_dir_x * sin(-0.05) + vars->player->dir_y * cos(-0.05);
      old_plane_x = vars->player->plane_x;
	  vars->player->plane_x = vars->player->plane_x * cos(-0.05)  - vars->player->plane_y * sin(-0.05);
      vars->player->plane_y = old_plane_x * sin(-0.05) + vars->player->plane_y * cos(-0.05);
	//never_eat_soggy_weetbix(vars->player, vars->player->token);
	//return (0);
}

int	player_move(int keycode, t_vars *vars)
{
	// if (vars->player->token == 'N' || vars->player->token == 'S')
	// 	ns_move(keycode, vars);
	// else
	// 	ew_move(keycode, vars);
	if (keycode == LEFT_KEY)
		look_left(vars);
	// if (keycode == RIGHT_KEY)
	// 	look_right(vars);
	mlx_destroy_image(vars->mlx_ptr, vars->img->img);
	free(vars->img);
	render_image(vars);
	return (0);
}
