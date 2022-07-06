/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:12:06 by jpfannku          #+#    #+#             */
/*   Updated: 2022/07/06 15:50:46 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// void draw_line(t_data *data, int x, int y, int len, int color)
// {
// 	int		i;
// 	int		j;
// 	int		limit;

// 	i = 0;
// 	while (i < len && (j = y + 1) < limit)
// 	{
// 		y = j;
// 		put_pixel(data, x, y, color);
// 		i++;
// 	}
// }

void verLine(int x, int y1, int y2, int color)
{
	
}

int	done(void)
{
	return (0);
}

int raycast(t_vars *vars)
{
	float 	plane_x;
	float 	plane_y;//the 2d raycaster version of camera plane
	int		x;
	int		w;
	int		h;
	float	ray_dir_x;
	float	ray_dir_y;
	int		camera_x;

	plane_x = 0;
	plane_y = 0.66;
	w = 640;
	h = 480;
	while(!done())
	{
		x = 0;
		while(x < w)
		{
			camera_x = 2 * x / w - 1; 
		//calculate ray position and direction
		 //cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
		 	ray_dir_x = vars->player->dir_x + plane_x * camera_x;
			ray_dir_y = vars->player->dir_y + plane_y * camera_x;
		//which box of the map we're in
			int mapX = vars->player->pos_x;
			int mapY = vars->player->pos_y;

		//length of ray from current position to next x or y-side
			float sideDistX;
			float sideDistY;

		//length of ray from one x or y-side to next x or y-side
		//these are derived as:
		//deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * ray_dir_x))
		//deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY))
		//which can be simplified to abs(|rayDir| / rayDirX) and abs(|rayDir| / rayDirY)
		//where |rayDir| is the length of the vector (rayDirX, rayDirY). Its length,
		//unlike (dirX, dirY) is not 1, however this does not matter, only the
		//ratio between deltaDistX and deltaDistY matters, due to the way the DDA
		//stepping further below works. So the values can be computed as below.
		// Division through zero is prevented, even though technically that's not
		// needed in C++ with IEEE 754 floating point values.
			float deltaDistX = sqrt(1 + (ray_dir_y * ray_dir_y) / (ray_dir_x * ray_dir_x));
			float deltaDistY = sqrt(1 + (ray_dir_x * ray_dir_x) / (ray_dir_y * ray_dir_y));

			float perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
			int stepX;
			int stepY;

			int hit = 0; //was there a wall hit?
			int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
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
		//perform DDA
			while(hit == 0)
			{
				//jump to next map square, either in x-direction, or in y-direction
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
				//Check if ray has hit a wall
				if(vars->map->map_arr[mapX][mapY] > 0) hit = 1;
			}
		//Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
		//hit to the camera plane. Euclidean to center camera point would give fisheye effect!
		//This can be computed as (mapX - posX + (1 - stepX) / 2) / ray_dir_x for side == 0, or same formula with Y
		//for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
		//because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
		//steps, but we subtract deltaDist once because one step more into the wall was taken above.
			if(side == 0) perpWallDist = (sideDistX - deltaDistX);
			else          perpWallDist = (sideDistY - deltaDistY);

		//Calculate height of line to draw on screen
			int lineHeight = (int)(h / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
			int drawStart = -lineHeight / 2 + h / 2;
			if(drawStart < 0) drawStart = 0;
			int drawEnd = lineHeight / 2 + h / 2;
			if(drawEnd >= h) drawEnd = h - 1;

		//draw the pixels of the stripe as a vertical line
			verLine(x, drawStart, drawEnd, color);
			x++;
		}
	}
}