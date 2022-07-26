/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:41:20 by jpfannku          #+#    #+#             */
/*   Updated: 2022/07/26 18:34:17 by Loui :)          ###   ########.fr       */
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
		return (-1);
	if (vars->map->map_arr[y][x] == ' ')
		return (-1);
	if (x <= 0 || x > vars->map->width - 2)
		return (-1);
	if (y <= 0 || y > vars->map->height - 2)
		return (-1);
	return (0);
}
