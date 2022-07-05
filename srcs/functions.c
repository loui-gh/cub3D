/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:27:35 by Loui :)           #+#    #+#             */
/*   Updated: 2022/07/05 15:07:32 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

// int		done(void)
// {
// 	return (0);
// }

// void	put_pixel(t_data *data, int x, int y, int color)
// {
// 	char	*dst;

// 	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }

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

int	mouse_click(t_vars *vars)
{
	ft_putstr("See you next time :)\n");
	mlx_destroy_window(vars->mlx_ptr, vars->mlx_win);
	exit(EXIT_SUCCESS);
	return (0);
}

int	esc(int keycode, t_vars *vars)
{
	if (keycode == 65307)
	{
		ft_putstr("See you next time ESC:)\n");
		mlx_destroy_window(vars->mlx_ptr, vars->mlx_win);
		exit(EXIT_SUCCESS);
	}
	return (0);
}


