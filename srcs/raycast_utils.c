/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 22:18:37 by Loui :)           #+#    #+#             */
/*   Updated: 2022/08/09 19:43:07 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

int	get_pix_colour(t_data *tex, int x, int y)
{
	unsigned int	*addr;
	int				colour;

	addr = (unsigned int *)tex->addr;
	colour = 0;
	if (x >= 0 && y >= 0 && x <= tex->width && y <= tex->height)
		colour = ((unsigned int *)addr)[64 * y + x];
	return (colour);
}

/*uses the side variable (which calculates if it's a n/s or w/e side
together with the coordinates of the player in relation to map's x/c coord.
to find which face of the block we are viewing*/

void	draw_image(int x, t_raycast *ray, t_vars *ptr)
{
	int	y;
	int	tex_y;

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)ray->tex_pos &(64 - 1);
		ray->tex_pos += ray->step;
		if (ray->side == 0 && ptr->player->pos_x < ray->map_x)
			put_pixel(ptr->img, x, y, \
				get_pix_colour(ptr->tex->west, ray->tex_x, tex_y));
		else if (ray->side == 0 && ptr->player->pos_x > ray->map_x)
			put_pixel(ptr->img, x, y, \
				get_pix_colour(ptr->tex->east, ray->tex_x, tex_y));
		else if (ray->side == 1 && ptr->player->pos_y < ray->map_y)
			put_pixel(ptr->img, x, y, \
				get_pix_colour(ptr->tex->north, ray->tex_x, tex_y));
		else
			put_pixel(ptr->img, x, y, \
				get_pix_colour(ptr->tex->south, ray->tex_x, tex_y));
		y++;
	}
}

void	ray_hit_wall(t_raycast *ray, t_vars *vars)
{
	ray->hit = 0;
	while (ray->hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += sqrt(1 + (ray->ray_dir_y * ray->ray_dir_y) \
				/ (ray->ray_dir_x * ray->ray_dir_x));
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += sqrt(1 + (ray->ray_dir_x * ray->ray_dir_x) \
				/ (ray->ray_dir_y * ray->ray_dir_y));
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (vars->map->map_arr[(int)ray->map_y][(int)ray->map_x] \
			&& vars->map->map_arr[(int)ray->map_y][(int)ray->map_x] == '1')
			ray->hit = 1;
	}
}
