/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:41:20 by jpfannku          #+#    #+#             */
/*   Updated: 2022/08/03 23:48:31 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"


//rotate to the left
//     if (keyDown(SDLK_LEFT))
//     {
//       //both camera direction and camera plane must be rotated
//       double oldDirX = dirX;
//       dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
//       dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
//       double oldPlaneX = planeX;
//       planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
//       planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
//     }
// int	look_left(t_vars *vars)
// {
// 	char	*dir;
// 	int		i;

// 	dir = "NESW";
// 	i = 0;
// 	while (dir[i] && vars->player->token != dir[i])
// 		i++;
// 	if (i > 0)
// 		vars->player->token = dir[i - 1];
// 	else
// 		vars->player->token = dir[3];
// 	never_eat_soggy_weetbix(vars->player, vars->player->token);
// 	return (0);
// }

// int	look_right(t_vars *vars)
// {
// 	char	*dir;
// 	int		i;

// 	dir = "NESW";
// 	i = 0;
// 	while (dir[i] && vars->player->token != dir[i])
// 		i++;
// 	if (i <= 2)
// 		vars->player->token = dir[i + 1];
// 	else
// 		vars->player->token = dir[0];
// 	never_eat_soggy_weetbix(vars->player, vars->player->token);
// 	return (0);
// }

// int	hit_wall(int x, int y, t_vars *vars)
// {
// 	if (!vars->map->map_arr[y][x])
// 		return (-1);
// 	if (vars->map->map_arr[y][x] == ' ')
// 		return (-1);
// 	if (x <= 0 || x > vars->map->width - 2)
// 		return (-1);
// 	if (y <= 0 || y > vars->map->height - 2)
// 		return (-1);
// 	return (0);
// }

// int	ns_move(int keycode, t_vars *vars)
// {
// 	if (vars->player->token == 'N')
// 	{
// 		if (keycode == D_KEY)
// 			go_east(vars, vars->map, vars->player);
// 		if (keycode == A_KEY)
// 			go_west(vars, vars->map, vars->player);
// 		if (keycode == S_KEY)
// 			go_south(vars, vars->map, vars->player);
// 		if (keycode == W_KEY)
// 			go_north(vars, vars->map, vars->player);
// 	}
// 	else
// 	{
// 		if (keycode == D_KEY)
// 			go_west(vars, vars->map, vars->player);
// 		if (keycode == A_KEY)
// 			go_east(vars, vars->map, vars->player);
// 		if (keycode == S_KEY)
// 			go_north(vars, vars->map, vars->player);
// 		if (keycode == W_KEY)
// 			go_south(vars, vars->map, vars->player);
// 	}
// 	return (0);
// }

// int	ew_move(int keycode, t_vars *vars)
// {
// 	if (vars->player->token == 'E')
// 	{
// 		if (keycode == D_KEY)
// 			go_south(vars, vars->map, vars->player);
// 		if (keycode == A_KEY)
// 			go_north(vars, vars->map, vars->player);
// 		if (keycode == S_KEY)
// 			go_west(vars, vars->map, vars->player);
// 		if (keycode == W_KEY)
// 			go_east(vars, vars->map, vars->player);
// 	}
// 	else
// 	{
// 		if (keycode == D_KEY)
// 			go_north(vars, vars->map, vars->player);
// 		if (keycode == A_KEY)
// 			go_south(vars, vars->map, vars->player);
// 		if (keycode == S_KEY)
// 			go_east(vars, vars->map, vars->player);
// 		if (keycode == W_KEY)
// 			go_west(vars, vars->map, vars->player);
// 	}
// 	return (0);
// }
