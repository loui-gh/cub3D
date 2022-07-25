/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_tex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:12:06 by jpfannku          #+#    #+#             */
/*   Updated: 2022/07/25 13:04:31 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

/*
plane_x, y== 0.9
*/

void	ray_hit_while(t_raycast *ray, t_vars *vars)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += \
				sqrt(1 + (ray->ray_dir_y * ray->ray_dir_y) / \
				(ray->ray_dir_x * ray->ray_dir_x));
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += sqrt(1 + \
				(ray->ray_dir_x * ray->ray_dir_x) / \
				(ray->ray_dir_y * ray->ray_dir_y));
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (vars->map->map_arr[ray->map_y][ray->map_x] == '1')
			ray->hit = 1;
	}
}

void	set_vectors(t_raycast *ray)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = 0;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (float)(sqrt(1 + (ray->ray_dir_y * ray->ray_dir_y) / \
			(ray->ray_dir_x * ray->ray_dir_x)));
	}
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = 0;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (float)(sqrt(1 + (ray->ray_dir_x * ray->ray_dir_x) / \
			(ray->ray_dir_y * ray->ray_dir_y)));
	}
}

void	fuck_wish_had_switch(t_raycast *ray, t_vars *vars)
{
	if (ray->side == 0)
		ray->perp_wall_dist = \
			(ray->map_x - vars->player->pos_x + \
			(1 - ray->step_x) / 2) / ray->ray_dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - vars->player->pos_y + \
			(1 - ray->step_y) / 2) / ray->ray_dir_y;
	ray->draw_start = -(HEIGHT / ray->perp_wall_dist) / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (HEIGHT / ray->perp_wall_dist) / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
	if (ray->side == 0)
		ray->wall_x = vars->player->pos_x + \
			ray->perp_wall_dist * ray->ray_dir_y;
	else
		ray->wall_x = vars->player->pos_y + \
			ray->perp_wall_dist * ray->ray_dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = ray->wall_x * vars->tex->north->height;
	if (ray->side == 0 && ray->ray_dir_x < 0)
		ray->tex_x = vars->tex->north->height - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y > 0)
		ray->tex_x = vars->tex->north->height - ray->tex_x - 1;
}

void	actual_raycasting_bit(t_raycast *ray, t_vars *vars)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		ray->ray_dir_x = vars->player->dir_x + \
			0.9 * vars->player->dir_y * (2 * x / (float)WIDTH - 1) * -1;
		ray->ray_dir_y = vars->player->dir_y + \
			0.9 * vars->player->dir_x * (2 * x / (float)WIDTH - 1);
		set_vectors(ray);
		ray->map_x = vars->player->pos_x;
		ray->map_y = vars->player->pos_y;
		ray_hit_while(ray, vars);
		fuck_wish_had_switch(ray, vars);
		fill_buffer(x, ray, vars);
		ray->step = 1.0 * vars->tex->north->height / \
					(HEIGHT / ray->perp_wall_dist);
		ray->tex_pos = (ray->draw_start - HEIGHT / 2 + \
				(HEIGHT / ray->perp_wall_dist) / 2) * ray->step;
		x++;
	}
}

int	raycast_tex(t_vars *vars)
{
	int			m;
	t_raycast	ray;
	t_data		*fl_c;

	m = 0;
	fl_c = floor_ceiling(vars);
	while (m < 1)
	{
		actual_raycasting_bit(&ray, vars);
		m++;
	}
	write_buffer_to_img(fl_c, vars->big_buff);
	mlx_put_image_to_window(vars->mlx_ptr, vars->mlx_win, fl_c->img, 0, 0);
	vars->img = fl_c;
	scrub_array(-1, vars);
	return (0);
}
