/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 20:30:31 by jpfannku          #+#    #+#             */
/*   Updated: 2022/07/07 20:32:10 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void verLine(int x, int y1, int y2, int color, t_data *data)
{
	int	i;

	i = y1;
	while(i < y2)
	{
		put_pixel(data, x, i, color);
		i++;
	}
}

void	draw_rectangle(t_data *img, int y1, int y2, int x, int colour)
{
	int	i;

	i = 0;
	while (i < x)
	{
		verLine(i, y1, y2, colour, img);
		i++;
	}
}

t_data	*floor_ceiling(t_vars *vars)
{
	int		w;
	int		h;
	t_data	*img;
	
	w = 640;
	h = 480;
	img = (t_data *)malloc(sizeof(t_data));
	img->img = mlx_new_image(vars->mlx_ptr, w, h);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);
	draw_rectangle(img, 0, h / 2, w, vars->tex->ceiling);
	draw_rectangle(img, h / 2, h, w, vars->tex->floor);
	return (img);
}
