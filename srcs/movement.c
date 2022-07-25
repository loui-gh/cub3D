/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 13:50:21 by jpfannku          #+#    #+#             */
/*   Updated: 2022/07/25 16:09:02 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

int	player_move(int keycode, t_vars *vars)
{
	if (keycode == 100)
		printf("right\n");
	if (keycode == 97)
		printf("left\n");
	if (keycode == 115)
		printf("down\n");
	if (keycode == 119)
		go_forward(vars);
	mlx_destroy_image(vars->mlx_ptr, vars->img->img);
	raycast_tex(vars);
	return (0);
}

int	go_forward(t_vars *vars)
{
	if (vars->player->pos_x + vars->player->dir_x >= vars->map->width || \
			vars->player->pos_y + vars->player->dir_x >= vars->map->height)
	{
		printf("edge of the map u silly bean\n");
		return (-1);
	}
	printf("%i\n", vars->player->pos_x);
	vars->map->map_arr[vars->player->pos_y][vars->player->pos_x] = 0;
	vars->player->pos_x += vars->player->dir_x;
	vars->player->pos_y += vars->player->dir_y;
	vars->map->map_arr[vars->player->pos_y][vars->player->pos_x] \
		= vars->player->token;
	return (0);
}
