/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 13:50:21 by jpfannku          #+#    #+#             */
/*   Updated: 2022/07/26 11:43:50 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

// int	go_right(t_vars *vars)
// {
// 	if (vars->player->token == 'N' || vars->player->token == 'S')
// 	{
// 		if (hit_wall(vars->player->pos_x - vars->player->dir_y, 
// 		vars->player->pos_y + vars->player->dir_x, vars) < 0)
// 			return (-1);
// 		else
// 			vars->player->pos_x -= vars->player->dir_y;
// 	}
// 	else
// 	{
// 		if (hit_wall(vars->player->pos_x + vars->player->dir_y, 
// 		vars->player->pos_y + vars->player->dir_x, vars) < 0)
// 			return (-1);
// 		else
// 			vars->player->pos_x += vars->player->dir_y;
// 	}
// 	vars->player->pos_y += vars->player->dir_x;
// 	return (0);
// }

// int	go_left(t_vars *vars)
// {
// 	if (vars->player->token == 'N' || vars->player->token == 'S')
// 	{
// 		if (hit_wall(vars->player->pos_x + vars->player->dir_y, 
// 		vars->player->pos_y - vars->player->dir_x, vars) < 0)
// 			return (-1);
// 		else
// 			vars->player->pos_x += vars->player->dir_y;
// 	}
// 	else
// 	{
// 		if (hit_wall(vars->player->pos_x - vars->player->dir_y, 
// 		vars->player->pos_y - vars->player->dir_x, vars) < 0)
// 			return (-1);
// 		else
// 			vars->player->pos_x -= vars->player->dir_y;
// 	}
// 	vars->player->pos_y -= vars->player->dir_x;
// 	return (0);
// }

int	go_west(t_vars *vars, t_map *map, t_player *player)
{
	if (map->map_arr[vars->player->pos_y][player->pos_x - 1] == '1')
	{
		printf("ummm that's a wall :)\n");
		return (0);
	}
	player->pos_x -= 1;
	return (0);
}

int	go_east(t_vars *vars, t_map *map, t_player *player)
{
	if (map->map_arr[vars->player->pos_y][player->pos_x + 1] == '1')
	{
		printf("ummm that's a wall :)\n");
		return (0);
	}
	player->pos_x += 1;
	return (0);
}

int	go_north(t_vars *vars, t_map *map, t_player *player)
{
	if (map->map_arr[vars->player->pos_y - 1][player->pos_x] == '1')
	{
		printf("ummm that's a wall :)\n");
		return (0);
	}
	player->pos_y -= 1;
	return (0);
}

int	go_south(t_vars *vars, t_map *map, t_player *player)
{
	if (map->map_arr[vars->player->pos_y + 1][player->pos_x] == '1')
	{
		printf("ummm that's a wall :)\n");
		return (0);
	}
	player->pos_y += 1;
	return (0);
}

// int	go_forward(t_vars *vars)
// {
// 	if (hit_wall(vars->player->pos_x + vars->player->dir_x, 
// 	vars->player->pos_y + vars->player->dir_y, vars) < 0)
// 		return (-1);
// 	vars->player->pos_x += vars->player->dir_x;
// 	vars->player->pos_y += vars->player->dir_y;
// 	return (0);
// }

// int	go_backward(t_vars *vars)
// {
// 	if (hit_wall(vars->player->pos_x + vars->player->dir_x * -1, 
// 	vars->player->pos_y + vars->player->dir_y * -1, vars) < 0)
// 		return (-1);
// 	vars->player->pos_x += vars->player->dir_x * -1;
// 	vars->player->pos_y += vars->player->dir_y * -1;
// 	return (0);
// }

int	ns_move(int keycode, t_vars *vars)
{
	if (vars->player->token == north)
}

int	player_move(int keycode, t_vars *vars)
{
	if (vars->player->token == 'N' || vars->player->token == 'S')
		ns_move(keycode, vars);
	if (keycode == 100)
		go_east(vars, vars->map, vars->player);
	if (keycode == 97)
		go_west(vars, vars->map, vars->player);
	if (keycode == 115)
		go_south(vars, vars->map, vars->player);
	if (keycode == 119)
		go_north(vars, vars->map, vars->player);
	if (keycode == 65361)
		look_left(vars);
	if (keycode == 65363)
		look_right(vars);
	printf("player x: %i, y: %i\n", vars->player->pos_x, vars->player->pos_y);
	mlx_destroy_image(vars->mlx_ptr, vars->img->img);
	raycast_tex(vars);
	return (0);
}
