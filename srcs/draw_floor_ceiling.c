/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_ceiling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 20:30:31 by jpfannku          #+#    #+#             */
/*   Updated: 2022/08/08 11:54:34 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

void	put_pixel(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/* "verLine" ft put into draw_ceiling, draw_floor
** norminette restriction on no. vars necessitated
** two sep fts to draw floor and ceiling.
** nested while loop draws vertical lines
*/

void	draw_ceiling(t_vars *vars, int y1, int y2, int x)
{
	int	i;
	int	j;

	i = 0;
	while (i < x)
	{
		j = y1;
		while (j < y2)
		{
			put_pixel(vars->img, i, j, vars->tex->ceiling);
			j++;
		}
		i++;
	}
}

void	draw_floor(t_vars *vars, int y1, int y2, int x)
{
	int	i;
	int	j;

	i = 0;
	while (i < x)
	{
		j = y1;
		while (j < y2)
		{
			put_pixel(vars->img, i, j, vars->tex->floor);
			j++;
		}
		i++;
	}
}

t_data	*floor_ceiling(t_vars *vars)
{
	int		w;
	int		h;

	w = WIDTH;
	h = HEIGHT;
	draw_ceiling(vars, 0, h / 2, w);
	draw_floor(vars, h / 2, h, w);
	return (vars->img);
}
