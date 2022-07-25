/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 13:50:21 by jpfannku          #+#    #+#             */
/*   Updated: 2022/07/25 23:34:36 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

int	go_right(t_vars *vars)
{
	if (vars->player->pos_y + vars->player->dir_x >= vars->map->height || \
		vars->player->pos_y + vars->player->dir_x <= 0)
	{
		printf("you're a stinky baby!\n");
		return(-1);
	}
	if (vars->player->token == 'N' || vars->player->token == 'S')
	{
		if (vars->player->pos_x - vars->player->dir_y <= 0 || \
			vars->player->pos_x - vars->player->dir_y > vars->map->width)
		{
			printf("bop");
			return (-1);
		}
		else
			vars->player->pos_x -= vars->player->dir_y;
	}
	else
	{
		if (vars->player->pos_x + vars->player->dir_y <= 0 ||\
			vars->player->pos_x + vars->player->dir_y > vars->map->width)
		{
			printf("bop");
			return (-1);
		}
		else
			vars->player->pos_x += vars->player->dir_y;
	}
	vars->player->pos_y += vars->player->dir_x;
	return (0);
}

int	go_left(t_vars *vars)
{
	vars->player->pos_y -= vars->player->dir_x;
	if (vars->player->token == 'N' || vars->player->token == 'S')
		vars->player->pos_x += vars->player->dir_y;
	else
		vars->player->pos_x -= vars->player->dir_y;
	return (0);
}

int	go_forward(t_vars *vars)
{
	if (vars->player->pos_x + vars->player->dir_x <= 0 || \
			vars->player->pos_y + vars->player->dir_y <= 0)
		return (-1);

	if (vars->player->pos_x + vars->player->dir_x > vars->map->width || \
			vars->player->pos_y + vars->player->dir_y > vars->map->height)
		return (-1);
	vars->player->pos_x += vars->player->dir_x;
	vars->player->pos_y += vars->player->dir_y;
	return (0);
}

int	go_backward(t_vars *vars)
{
	if (vars->player->pos_x - vars->player->dir_x <= 0 || \
			vars->player->pos_y - vars->player->dir_y <= 0)
		return (-1);

	if (vars->player->pos_x - vars->player->dir_x > vars->map->width || \
			vars->player->pos_y - vars->player->dir_y > vars->map->height)
		return (-1);
	vars->player->pos_x += vars->player->dir_x * -1;
	vars->player->pos_y += vars->player->dir_y * -1;
	return (0);
}

int	player_move(int keycode, t_vars *vars)
{
	if (keycode == 100)
		go_right(vars);
	if (keycode == 97)
		go_left(vars);
	if (keycode == 115)
		go_backward(vars);
	if (keycode == 119)
		go_forward(vars);
	mlx_destroy_image(vars->mlx_ptr, vars->img->img);
	raycast_tex(vars);
	return (0);
}
