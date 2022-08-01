/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_tex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:12:06 by jpfannku          #+#    #+#             */
/*   Updated: 2022/08/01 19:31:56 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

void	set_y_vectors(t_raycast *ray, t_vars *vars)
{
	if (ray->ray_dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = ((float)(sqrt(1 + (ray->ray_dir_x * \
		ray->ray_dir_x) / (ray->ray_dir_y * ray->ray_dir_y)))) * \
		(vars->player->pos_y - ray->map_y);
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = ((float)(sqrt(1 + (ray->ray_dir_x * \
		ray->ray_dir_x) / (ray->ray_dir_y * ray->ray_dir_y)))) * \
		(ray->map_y - vars->player->pos_y + 1.0);
	}
}

void	set_x_vectors(t_raycast *ray, t_vars *vars)
{
	if (ray->ray_dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = ((float)(sqrt(1 + (ray->ray_dir_y * \
		ray->ray_dir_y) / (ray->ray_dir_x * ray->ray_dir_x)))) * \
		(vars->player->pos_x - ray->map_x);
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = ((float)(sqrt(1 + (ray->ray_dir_y * \
		ray->ray_dir_y) / (ray->ray_dir_x * ray->ray_dir_x)))) * \
		(ray->map_x - vars->player->pos_x + 1.0);
	}
}

void	find_wall_coord(t_raycast *ray, t_vars *vars)
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
	ray->tex_x = (int)(ray->wall_x * (double)vars->tex->north->height);
	if (ray->side == 0 && ray->ray_dir_x < 0)
		ray->tex_x = vars->tex->north->height - ray->tex_x - 1;
	if (ray->side == 1 && ray->ray_dir_y > 0)
		ray->tex_x = vars->tex->north->height - ray->tex_x - 1;
}

void	raycast(t_raycast *ray, t_vars *vars)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		ray->ray_dir_x = vars->player->dir_x + \
			0.66 * vars->player->dir_y * (2 * x / (float)WIDTH - 1) * -1;
		ray->ray_dir_y = vars->player->dir_y + \
			0.66 * vars->player->dir_x * (2 * x / (float)WIDTH - 1);
		ray->map_x = (int)vars->player->pos_x;
		ray->map_y = (int)vars->player->pos_y;
		set_x_vectors(ray, vars);
		set_y_vectors(ray, vars);
		ray_hit_wall(ray, vars);
		find_wall_coord(ray, vars);
		ray->step = 1.0 * vars->tex->north->height / \
				(HEIGHT / ray->perp_wall_dist);
		ray->tex_pos = (ray->draw_start - HEIGHT / 2 + \
				(HEIGHT / ray->perp_wall_dist) / 2) * ray->step;
		fill_buffer(x, ray, vars);
		x++;
	}
}

int	render_image(t_vars *vars)
{
	int			m;
	t_raycast	*ray;
	t_data		*fl_c;

	m = 0;
	fl_c = floor_ceiling(vars);
	ray = (t_raycast *)ft_calloc(sizeof(t_raycast), 1);
	while (m < 1)
	{
		raycast(ray, vars);
		m++;
	}
	free(ray);
	write_buffer_to_img(fl_c, vars->big_buff);
	mlx_put_image_to_window(vars->mlx_ptr, vars->mlx_win, fl_c->img, 0, 0);
	vars->img = fl_c;
	scrub_array(-1, vars);
	return (0);
}
