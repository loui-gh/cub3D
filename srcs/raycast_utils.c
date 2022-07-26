/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 22:18:37 by Loui :)           #+#    #+#             */
/*   Updated: 2022/07/26 23:44:00 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

int	get_pix_colour(t_data *tex, int x, int y)
{
	// int i = 1;
	if (x >= 0 && y >= 0 && x <= tex->width && y <= tex->height)
	{
		if (y != 64 && x != 64)
			return (*(int *)(tex->img + (4 * tex->width * y) + (4 * x)));
	}
	return (0);
}

/*uses the side variable (which calculates if it's a n/s or w/e side
together with the coordinates of the player in relation to map's x/c coord.
to find which face of the block we are viewing*/

void	fill_buffer(int x, t_raycast *ray, t_vars *ptr)
{
	int	y;
	int	tex_y;

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)ray->tex_pos;
		ray->tex_pos += ray->step;
		if (ray->side == 0 && ptr->player->pos_x < ray->map_x)
			ptr->big_buff[y][x] = \
				get_pix_colour(ptr->tex->west, ray->tex_x, tex_y);
		else if (ray->side == 0 && ptr->player->pos_x > ray->map_x)
			ptr->big_buff[y][x] = \
				get_pix_colour(ptr->tex->east, ray->tex_x, tex_y);
		else if (ray->side == 1 && ptr->player->pos_y < ray->map_y)
			ptr->big_buff[y][x] = \
				get_pix_colour(ptr->tex->north, ray->tex_x, tex_y);
		else
			ptr->big_buff[y][x] = \
				get_pix_colour(ptr->tex->south, ray->tex_x, tex_y);
		y++;
	}
}

void	write_buffer_to_img(t_data *img, int **buffer)
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
