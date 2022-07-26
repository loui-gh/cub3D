/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:41:20 by jpfannku          #+#    #+#             */
/*   Updated: 2022/07/26 12:22:56 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

int	look_left(t_vars *vars)
{
	char	*dir;
	int		i;

	dir = "NESW";
	i = 0;
	while (dir[i] && vars->player->token != dir[i])
		i++;
	if (i > 0)
		vars->player->token = dir[i - 1];
	else
		vars->player->token = dir[3];
	never_eat_soggy_weetbix(vars->player, vars->player->token);
	return (0);
}

int	look_right(t_vars *vars)
{
	char	*dir;
	int		i;

	dir = "NESW";
	i = 0;
	while (dir[i] && vars->player->token != dir[i])
		i++;
	if (i <= 2)
		vars->player->token = dir[i + 1];
	else
		vars->player->token = dir[0];
	never_eat_soggy_weetbix(vars->player, vars->player->token);
	return (0);
}

int	hit_wall(int x, int y, t_vars *vars)
{
	if (!vars->map->map_arr[y][x])
	{
		printf("no exist\n");
		return (-1);
	}	
	if (vars->map->map_arr[y][x] == ' ')
	{
		printf("hole\n");
		return (-1);
	}	
	if (x <= 0 || x > vars->map->width - 2)
	{
		printf("array scope x\n");
		return (-1);
	}	
	if (y <= 0 || y > vars->map->height - 2)
	{
		printf("array scope y\n");
		return (-1);
	}	
	return (0);
}

int	ns_move(int keycode, t_vars *vars)
{
	if (vars->player->token == 'N')
	{
		if (keycode == 100)
			go_east(vars, vars->map, vars->player);
		if (keycode == 97)
			go_west(vars, vars->map, vars->player);
		if (keycode == 115)
			go_south(vars, vars->map, vars->player);
		if (keycode == 119)
			go_north(vars, vars->map, vars->player);
	}
	else
	{
		if (keycode == 100)
			go_west(vars, vars->map, vars->player);
		if (keycode == 97)
			go_east(vars, vars->map, vars->player);
		if (keycode == 115)
			go_north(vars, vars->map, vars->player);
		if (keycode == 119)
			go_south(vars, vars->map, vars->player);
	}
	return (0);
}

int	ew_move(int keycode, t_vars *vars)
{
	if (vars->player->token == 'E')
	{
		if (keycode == 100)
			go_south(vars, vars->map, vars->player);
		if (keycode == 97)
			go_north(vars, vars->map, vars->player);
		if (keycode == 115)
			go_west(vars, vars->map, vars->player);
		if (keycode == 119)
			go_east(vars, vars->map, vars->player);
	}
	else
	{
		if (keycode == 100)
			go_north(vars, vars->map, vars->player);
		if (keycode == 97)
			go_south(vars, vars->map, vars->player);
		if (keycode == 115)
			go_east(vars, vars->map, vars->player);
		if (keycode == 119)
			go_west(vars, vars->map, vars->player);
	}
	return (0);
}
