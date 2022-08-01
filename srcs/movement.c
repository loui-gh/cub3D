/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 13:50:21 by jpfannku          #+#    #+#             */
/*   Updated: 2022/08/01 19:34:02 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

int	go_west(t_vars *vars, t_map *map, t_player *player)
{
	if (map->map_arr[(int)vars->player->pos_y][(int)player->pos_x - 1] == '1')
		return (0);
	player->pos_x -= 1;
	return (0);
}

int	go_east(t_vars *vars, t_map *map, t_player *player)
{
	if (map->map_arr[(int)vars->player->pos_y][(int)player->pos_x + 1] == '1')
		return (0);
	player->pos_x += 1;
	return (0);
}

int	go_north(t_vars *vars, t_map *map, t_player *player)
{
	if (map->map_arr[(int)vars->player->pos_y - 1][(int)player->pos_x] == '1')
		return (0);
	player->pos_y -= 1;
	return (0);
}

int	go_south(t_vars *vars, t_map *map, t_player *player)
{
	if (map->map_arr[(int)vars->player->pos_y + 1][(int)player->pos_x] == '1')
		return (0);
	player->pos_y += 1;
	return (0);
}

int	player_move(int keycode, t_vars *vars)
{
	if (vars->player->token == 'N' || vars->player->token == 'S')
		ns_move(keycode, vars);
	else
		ew_move(keycode, vars);
	if (keycode == LEFT_KEY)
		look_left(vars);
	if (keycode == RIGHT_KEY)
		look_right(vars);
	mlx_destroy_image(vars->mlx_ptr, vars->img->img);
	free(vars->img);
	render_image(vars);
	return (0);
}
