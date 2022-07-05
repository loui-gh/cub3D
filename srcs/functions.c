/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:27:35 by Loui :)           #+#    #+#             */
/*   Updated: 2022/07/05 20:14:18 by Loui :)          ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc != 2)
		exit_msg("enter cmd like this --> ./cub3D *.cub\n");
	
	//init_textures
	//create map array
	vars.mlx_ptr = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx_ptr, 720, 1080, "Hello world!");
	mlx_hook(vars.mlx_win, 2, 27, esc, &vars);
	mlx_hook(vars.mlx_win, 17, (1L << 17), mouse_click, &vars);
	mlx_loop(vars.mlx_ptr);
}
