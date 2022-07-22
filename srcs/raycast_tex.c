/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_tex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:12:06 by jpfannku          #+#    #+#             */
/*   Updated: 2022/07/22 23:51:07 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

/*
plane_x, y== 0.9
*/
int	raycast_tex(t_vars *vars)
{
	int		m;
	int		x;
	float	ray_dir_x;
	float	ray_dir_y;
	float	sideDistX;
	float	sideDistY;
	float	perpWallDist;
	t_data	*fl_c;
	int buffer[HEIGHT][WIDTH];

	m = 0;
	fl_c = floor_ceiling(vars);
	while(m < 1)
	{
		x = 0; 
		while(x < WIDTH)
		{
		 	ray_dir_x = vars->player->dir_x + 0.9 * vars->player->dir_y * (2 * x / (float)WIDTH - 1);
			ray_dir_y = vars->player->dir_y + 0.9 * vars->player->dir_x * (2 * x / (float)WIDTH - 1);
			int stepX;
			int stepY;
			
			if(ray_dir_x < 0)
			{
				stepX = -1;
				sideDistX = 0;
			}
			else
			{
				stepX = 1;
				sideDistX = (float)(sqrt(1 + (ray_dir_y * ray_dir_y) / (ray_dir_x * ray_dir_x)));
			}
			if(ray_dir_y < 0)
			{
				stepY = -1;
				sideDistY = 0;
			}
			else
			{
				stepY = 1;
				sideDistY = (float)(sqrt(1 + (ray_dir_x * ray_dir_x) / (ray_dir_y * ray_dir_y)));
			}
			int mapX = vars->player->pos_x;
			int mapY = vars->player->pos_y;
			int hit = 0;
			int side;
			while(hit == 0)
			{
				if(sideDistX < sideDistY)
				{
					sideDistX += sqrt(1 + (ray_dir_y * ray_dir_y) / (ray_dir_x * ray_dir_x));
					mapX += stepX;
					side = 0;
				}
				else
				{
					sideDistY += sqrt(1 + (ray_dir_x * ray_dir_x) / (ray_dir_y * ray_dir_y));
					mapY += stepY;
					side = 1;
				}
				if(vars->map->map_arr[mapY][mapX] == '1') hit = 1;
			}	
			if	(side == 0)
				perpWallDist = (mapX - vars->player->pos_x + (1 - stepX) / 2) / ray_dir_x;
			else
				perpWallDist = (mapY - vars->player->pos_y + (1 - stepY) / 2) / ray_dir_y;
	
			int drawStart = -(HEIGHT/ perpWallDist) / 2 + HEIGHT/ 2;
			if(drawStart < 0) 
				drawStart = 0;
			int drawEnd = (HEIGHT/ perpWallDist) / 2 + HEIGHT/ 2;
			if(drawEnd >= HEIGHT)
				drawEnd = HEIGHT- 1;

			double wallX;
			if(side == 0)
				wallX = vars->player->pos_x + perpWallDist * ray_dir_y;
			else
				wallX = vars->player->pos_y + perpWallDist * ray_dir_x;
			wallX -= floor(wallX);
			int texX = wallX * vars->tex->north->height;
			if(side == 0 && ray_dir_x < 0)
				texX = vars->tex->north->height - texX - 1;
			if(side == 1 && ray_dir_y > 0)
				texX = vars->tex->north->height - texX - 1;
			double step = 1.0 * vars->tex->north->height / (HEIGHT/ perpWallDist);
			double texPos = (drawStart - HEIGHT/ 2 + (HEIGHT/ perpWallDist) / 2) * step; //
			int y = drawStart;
			int 	texY;
			while( y < drawEnd)
			{
				texY = (int)texPos;
				texPos += step;
				buffer[y][x] = get_pix_colour(vars->tex->north, texX, texY);
				y++;
			}
			x++;
			if (x == 31)
				printf("beep");
		}
		m++;
	}
	print_buffer(buffer, fl_c);
	mlx_put_image_to_window(vars->mlx_ptr, vars->mlx_win, fl_c->img, 0, 0);
	vars->img = fl_c;
	return (0);
}

void	print_buffer(int buffer, t_data *ptr)
{
	int	x = 0;
	int	y = 0;
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			if (buffer[y][x] !=  0)
				put_pixel(ptr, x, y, buffer[y][x]);
			x++;
		}
		x = 0;
		y++;
	}
}