/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 22:18:37 by Loui :)           #+#    #+#             */
/*   Updated: 2022/07/23 22:05:59 by Loui :)          ###   ########.fr       */
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

void	fill_buffer(int x, t_raycast *ray, t_vars *ptr)
{
	int	y;
	int	tex_y;

	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)ray->tex_pos;
		ray->tex_pos += ray->step;
		ptr->big_buff[y][x] = \
			get_pix_colour(ptr->tex->north, ray->tex_x, tex_y);
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
