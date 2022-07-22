/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_tex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:12:06 by jpfannku          #+#    #+#             */
/*   Updated: 2022/07/22 22:45:06 by Loui :)          ###   ########.fr       */
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
	float 	sideDistX;
	float 	sideDistY;
	float 	deltaDistX;
	float 	deltaDistY;
	float 	perpWallDist;
	int 	texY;
	t_data *fl_c;
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
			int mapX = vars->player->pos_x;
			int mapY = vars->player->pos_y;
			deltaDistX = sqrt(1 + (ray_dir_y * ray_dir_y) / (ray_dir_x * ray_dir_x));
			deltaDistY = sqrt(1 + (ray_dir_x * ray_dir_x) / (ray_dir_y * ray_dir_y));
			int stepX;
			int stepY;

			int hit = 0;
			int side;
			if(ray_dir_x < 0)
			{
				stepX = -1;
				sideDistX = (vars->player->pos_x - mapX) * deltaDistX;
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - vars->player->pos_x) * deltaDistX;
			}
			if(ray_dir_y < 0)
			{
				stepY = -1;
				sideDistY = (vars->player->pos_y - mapY) * deltaDistY;
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - vars->player->pos_y) * deltaDistY;
			}
			while(hit == 0)
			{
				if(sideDistX < sideDistY)
				{
					sideDistX += deltaDistX;
					mapX += stepX;
					side = 0;
				}
				else
				{
					sideDistY += deltaDistY;
					mapY += stepY;
					side = 1;
				}
				if(vars->map->map_arr[mapY][mapX] == '1') hit = 1;
			}	
			if	(side == 0)
				perpWallDist = (mapX - vars->player->pos_x + (1 - stepX) / 2) / ray_dir_x;
			else
				perpWallDist = (mapY - vars->player->pos_y + (1 - stepY) / 2) / ray_dir_y;
	
			int lineHeight = (HEIGHT/ perpWallDist);
			int drawStart = -lineHeight / 2 + HEIGHT/ 2;
			if(drawStart < 0) drawStart = 0;
			int drawEnd = lineHeight / 2 + HEIGHT/ 2;
			if(drawEnd >= HEIGHT) drawEnd = HEIGHT- 1;

			double wallX;
			if(side == 0) wallX = vars->player->pos_x + perpWallDist * ray_dir_y;
			else          wallX = vars->player->pos_y + perpWallDist * ray_dir_x;
			wallX -= floor(wallX);
			int texX = wallX * vars->tex->north->height;
			if(side == 0 && ray_dir_x < 0) texX = vars->tex->north->height - texX - 1;
			if(side == 1 && ray_dir_y > 0) texX = vars->tex->north->height - texX - 1;
			double step = 1.0 * vars->tex->north->height / lineHeight;
			double texPos = (drawStart - HEIGHT/ 2 + lineHeight / 2) * step; //
			for(int y = drawStart; y < drawEnd; y++)
			{
				texY = (int)texPos;
				texPos += step;
				buffer[y][x] = get_pix_colour(vars->tex->north, texX, texY);
			}
			x++;
			if (x == 31)
				printf("beep");
		}
		m++;
	}
	x = 0;
	int y = 0;
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			if (buffer[y][x] !=  0)
				put_pixel(fl_c, x, y, buffer[y][x]);
			x++;
		}
		x = 0;
		y++;
	}
	mlx_put_image_to_window(vars->mlx_ptr, vars->mlx_win, fl_c->img, 0, 0);
	vars->img = fl_c;
	return (0);
}