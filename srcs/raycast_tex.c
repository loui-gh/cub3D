/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_tex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 15:12:06 by jpfannku          #+#    #+#             */
/*   Updated: 2022/07/19 11:19:59 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

int	get_pix_colour(t_data *tex, int x, int y)
{
	if (x >= 0 && y >= 0 && x <= tex->width && x <= tex->height)
		return (*(int*)(tex->img + (4 * tex->width * y) + (4 * x)));
	else 
		return (0);
}

int	raycast_tex(t_vars *vars)
{
	int		m;
	float 	plane_x;
	float 	plane_y;//the 2d raycaster version of camera plane
	float	x;
	float	w;
	float	h;
	float 	sideDistX;
	float 	sideDistY;
	float 	deltaDistX;
	float 	deltaDistY;
	float 	perpWallDist;
	int 	texY;
	//t_data	data;
	t_data *fl_c;

	m = 0;
	plane_x = 0.9 * vars->player->dir_y; //math?? direction vector needs to be perpendicular to camera plane always
	plane_y = 0.9 * vars->player->dir_x; //field of view (1 == 90 degree)
	w = 640;
	h = 480;
	//data.img = mlx_new_image(vars->mlx_ptr, w, h);
	//data.addr = mlx_get_data_addr(data.img, &data.bits_per_pixel, &data.line_length, &data.endian);
	//int color = 0xFFFFFF;
	fl_c = floor_ceiling(vars);
	//mlx_put_image_to_window(vars->mlx_ptr, vars->mlx_win, fl_c->img, 0, 0);
	while(m < 1) // checking for movement
	{
		x = 0; // ray counter 
		while(x < w) // calculate a single snapshot (frame)
		{
			float camera_x = 2 * x / (float)w - 1; //changed it back to float from no typecast
		 //calculate ray position and direction
		 //cameraX = 2 * x / (double)w - 1; //x-coordinate in camera space
		 	float ray_dir_x = vars->player->dir_x + plane_x * camera_x;
			float ray_dir_y = vars->player->dir_y + plane_y * camera_x;
			//printf("dirx: %f, diry: %f\n", ray_dir_x, ray_dir_y);
		 //coordinates of the ray visual (clarify)?????
			int mapX = vars->player->pos_x;
			int mapY = vars->player->pos_y;

		//length of ray from current position to next x or y-side
		// Ray position?
			//float sideDistX;
			//float sideDistY;

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
			deltaDistX = sqrt(1 + (ray_dir_y * ray_dir_y) / (ray_dir_x * ray_dir_x));
			deltaDistY = sqrt(1 + (ray_dir_x * ray_dir_x) / (ray_dir_y * ray_dir_y));

			//float perpWallDist;

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
					//color = 0x0113d57;
				}
				else
				{
					sideDistY += deltaDistY;
					mapY += stepY;
					side = 1;
					//color = 0x086479A;
				}
				//Check if ray has hit a wall
				if(vars->map->map_arr[mapY][mapX] == '1') hit = 1; //switched Y and X 
			}	
		//Calculate distance projected on camera direction. This is the shortest distance from the point where the wall is
		//hit to the camera plane. Euclidean to center camera point would give fisheye effect!
		//This can be computed as (mapX - posX + (1 - stepX) / 2) / ray_dir_x for side == 0, or same formula with Y
		//for size == 1, but can be simplified to the code below thanks to how sideDist and deltaDist are computed:
		//because they were left scaled to |rayDir|. sideDist is the entire length of the ray above after the multiple
		//steps, but we subtract deltaDist once because one step more into the wall was taken above.
			// if	(side == 0)
			// 	perpWallDist = (sideDistX - deltaDistX);
			// else          
			// 	perpWallDist = (sideDistY - deltaDistY);
			if	(side == 0)
				perpWallDist = (mapX - vars->player->pos_x + (1 - stepX) / 2) / ray_dir_x;
			else
				perpWallDist = (mapY - vars->player->pos_y + (1 - stepY) / 2) / ray_dir_y;
			//printf("wall dist: %f\n", perpWallDist);

		//Calculate height of line to draw on screen
			int lineHeight = (h / perpWallDist);

				//NEW
      //calculate lowest and highest pixel to fill in current stripe
			int drawStart = -lineHeight / 2 + h / 2;
			if(drawStart < 0) drawStart = 0;
			int drawEnd = lineHeight / 2 + h / 2;
			if(drawEnd >= h) drawEnd = h - 1;

			//calculate value of wallX
			double wallX; //where exactly the wall was hit
			if(side == 0) wallX = vars->player->pos_x + perpWallDist * ray_dir_y;
			else          wallX = vars->player->pos_y + perpWallDist * ray_dir_x;
			wallX -= floor(wallX);
			
			//x coordinate on the texture
			int texX = wallX * 64;
			if(side == 0 && ray_dir_x < 0) texX = 64 - texX - 1;
			if(side == 1 && ray_dir_y > 0) texX = 64 - texX - 1;

			// How much to increase the texture coordinate per screen pixel
			double step = 1.0 * 64 / lineHeight;
			// Starting texture coordinate
			double texPos = (drawStart - h / 2 + lineHeight / 2) * step;
			for(int y = drawStart; y < drawEnd; y++)
			{
				// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
				texY = (int)texPos;
				texPos += step;
				put_pixel(fl_c, x, y, get_pix_colour(vars->tex->north, texX, texY));
			}
			x++;
			if (x == 31)
				printf("beep");
		}
		m++;
	}
	mlx_put_image_to_window(vars->mlx_ptr, vars->mlx_win, fl_c->img, 0, 0);
	vars->img = fl_c;
	return (0);
}