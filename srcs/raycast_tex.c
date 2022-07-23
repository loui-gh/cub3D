/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_tex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:12:06 by jpfannku          #+#    #+#             */
/*   Updated: 2022/07/23 12:20:01 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

/*
plane_x, y== 0.9
*/

void	write_buffer(int x, t_raycast *ray, t_vars *ptr)
{
	int	y; //need?
	int	tex_y;

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)ray->tex_pos;
		ray->tex_pos += ray->step;
		ptr->big_buff[y][x] = get_pix_colour(ptr->tex->north, ray->tex_x, tex_y);
		y++;
	}
}

void	draw_buffer(t_data *img, int **buffer)
{
	int	x;
	int	y;

	y = 0;
	x = 0;
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			if (buffer[y][x] != -1)
				put_pixel(img, x, y, buffer[y][x]);
			x++;
		}
		x = 0;
		y++;
	}
}

int	raycast_tex(t_vars *vars)
{
	int			m;
	int			x;
	t_raycast	ray;


	t_data	*fl_c;
	m = 0;
	fl_c = floor_ceiling(vars);
	while(m < 1)
	{
		x = 0; 
		while(x < WIDTH)
		{
		 	ray_dir_x = vars->player->dir_x + 0.9 * vars->player->dir_y * (2 * x / (float)WIDTH - 1);
			ray_dir_y = vars->player->dir_y + 0.9 * vars->player->dir_x * (2 * x / (float)WIDTH - 1);
			if(ray_dir_x < 0)
			{
				step_x = -1;
				side_dist_x = 0;
			}
			else
			{
				step_x = 1;
				side_dist_x = (float)(sqrt(1 + (ray_dir_y * ray_dir_y) / (ray_dir_x * ray_dir_x)));
			}
			if(ray_dir_y < 0)
			{
				step_y = -1;
				side_dist_y = 0;
			}
			else
			{
				step_y = 1;
				side_dist_y = (float)(sqrt(1 + (ray_dir_x * ray_dir_x) / (ray_dir_y * ray_dir_y)));
			}
			map_x = vars->player->pos_x;
			map_y = vars->player->pos_y;
			hit = 0;
			while(hit == 0)
			{
				if(side_dist_x < side_dist_y)
				{
					side_dist_x += sqrt(1 + (ray_dir_y * ray_dir_y) / (ray_dir_x * ray_dir_x));
					map_x += step_x;
					side = 0;
				}
				else
				{
					side_dist_y += sqrt(1 + (ray_dir_x * ray_dir_x) / (ray_dir_y * ray_dir_y));
					map_y += step_y;
					side = 1;
				}
				if(vars->map->map_arr[map_y][map_x] == '1') hit = 1;
			}	
			if	(side == 0)
				perp_wall_dist = (map_x - vars->player->pos_x + (1 - step_x) / 2) / ray_dir_x;
			else
				perp_wall_dist = (map_y - vars->player->pos_y + (1 - step_y) / 2) / ray_dir_y;
	
			draw_start = -(HEIGHT/ perp_wall_dist) / 2 + HEIGHT/ 2;
			if(draw_start < 0) 
				draw_start = 0;
			draw_end = (HEIGHT/ perp_wall_dist) / 2 + HEIGHT/ 2;
			if(draw_end >= HEIGHT)
				draw_end = HEIGHT- 1;
			if(side == 0)
				wall_x = vars->player->pos_x + perp_wall_dist * ray_dir_y;
			else
				wall_x = vars->player->pos_y + perp_wall_dist * ray_dir_x;
			wall_x -= floor(wall_x);
			tex_x = wall_x * vars->tex->north->height;
			if(side == 0 && ray_dir_x < 0)
				tex_x = vars->tex->north->height - tex_x - 1;
			if(side == 1 && ray_dir_y > 0)
				tex_x = vars->tex->north->height - tex_x - 1;
			
			//draw buffer
			//set to zero ft
			step = 1.0 * vars->tex->north->height / (HEIGHT/ perp_wall_dist);
			tex_pos = (draw_start - HEIGHT/ 2 + (HEIGHT/ perp_wall_dist) / 2) * step; //
			x++;
			if (x == 31)
				printf("beep");
		}
		m++;
	}
	draw_buffer(fl_c, vars->big_buff);
	mlx_put_image_to_window(vars->mlx_ptr, vars->mlx_win, fl_c->img, 0, 0);
	vars->img = fl_c;
	scrub_array(-1, vars);
	return (0);
}