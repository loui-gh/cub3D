/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   raycast.c									  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/07/06 15:12:06 by jpfannku		  #+#	#+#			 */
/*   Updated: 2022/08/02 19:17:54 by Loui :)		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../incl/raycast.h"

void	set_y_vectors(t_raycast *ray, t_vars *vars)
{
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = ((float)(sqrt(1 + (ray->dir_x * \
		ray->dir_x) / (ray->dir_y * ray->dir_y)))) * \
		(vars->player->pos_y - ray->map_y);
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = ((float)(sqrt(1 + (ray->dir_x * \
		ray->dir_x) / (ray->dir_y * ray->dir_y)))) * \
		(ray->map_y - vars->player->pos_y + 1.0);
	}
}

void	set_x_vectors(t_raycast *ray, t_vars *vars)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = ((float)(sqrt(1 + (ray->dir_y * \
		ray->dir_y) / (ray->dir_x * ray->dir_x)))) * \
		(vars->player->pos_x - ray->map_x);
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = ((float)(sqrt(1 + (ray->dir_y * \
		ray->dir_y) / (ray->dir_x * ray->dir_x)))) * \
		(ray->map_x - vars->player->pos_x + 1.0);
	}
}

void	find_wall_coord(t_raycast *ray, t_vars *vars)
{
	if (ray->side == 0)
		ray->perp_wall_dist = \
			(ray->map_x - vars->player->pos_x + \
			(1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - vars->player->pos_y + \
			(1 - ray->step_y) / 2) / ray->dir_y;
	ray->draw_start = -(HEIGHT / ray->perp_wall_dist) / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (HEIGHT / ray->perp_wall_dist) / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
	if (ray->side == 0)
		ray->wall_x = vars->player->pos_y + \
			ray->perp_wall_dist * ray->dir_y;
	else
		ray->wall_x = vars->player->pos_x + \
			ray->perp_wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)vars->tex->north->height);
	if (ray->side == 0 && ray->dir_x > 0)
		ray->tex_x = vars->tex->north->height - ray->tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		ray->tex_x = vars->tex->north->height - ray->tex_x - 1;
}

void	raycast(t_raycast *ray, t_vars *vars)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		//CHANGED
		ray->camera_x = 2 * x / (double)WIDTH - 1;
		ray->dir_x = vars->player->dir_x + vars->player->plane_x * ray->camera_x;
		ray->dir_y = vars->player->dir_y + vars->player->plane_y * ray->camera_x;
		
		//changed map_x and y to ints in header file
		ray->map_x = (int)vars->player->pos_x;
		ray->map_y = (int)vars->player->pos_y;

		if (ray->dir_x == 0)
			ray->delta_dist_x = 1e30;
		else
			ray->delta_dist_x = fabs(1 / ray->dir_x);
		if (ray->dir_y == 0)
			ray->delta_dist_y = 1e30;
		else
			ray->delta_dist_y = fabs(1 / ray->dir_y);
		
		//calculate step and side dist
		//replaces set_x/y_vectors fts --wtf did that sqrt ft come from??
		if (ray->dir_x < 0)
		{
			ray->step_x = -1;
			ray->side_dist_x = (vars->player->pos_x - ray->map_x) * ray->delta_dist_x;
		}
		else
		{
			ray->step_x = 1;
			ray->side_dist_x = (ray->map_x + 1.0 - vars->player->pos_x) * ray->delta_dist_x;
		}
		if (ray->dir_y < 0)
		{
			ray->step_y = -1;
			ray->side_dist_y =	(vars->player->pos_y - ray->map_y) * ray->delta_dist_y;
		}
		else
		{
			ray->step_y = 1;
			ray->side_dist_y = (ray->map_y + 1.0 - vars->player->pos_y) * ray->delta_dist_y;
		}
		//set_x_vectors(ray, vars);
		//set_y_vectors(ray, vars);
		ray_hit_wall(ray, vars);
		//don't know how wall_coord works
		find_wall_coord(ray, vars);
		ray->step = 1.0 * vars->tex->north->height / \
				(int)(HEIGHT / ray->perp_wall_dist);
		ray->tex_pos = (ray->draw_start - HEIGHT / 2 + \
				(int)(HEIGHT / ray->perp_wall_dist) / 2) * ray->step;
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
