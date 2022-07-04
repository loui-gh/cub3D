#include "../incl/raycast.h"

int		done(void)
{
	return (0);
}

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

int	mouse_click(t_vars *vars)
{
	printf("See you next time :)\n");
	mlx_destroy_window(vars->mlx_ptr, vars->mlx_win);
	exit(EXIT_SUCCESS);
	return (0);
}

int	esc(int keycode, t_vars *vars)
{
	if (keycode == 65307)
	{
		printf("See you next time ESC:)\n");
		mlx_destroy_window(vars->mlx_ptr, vars->mlx_win);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	main(void)
{
	t_vars	vars;
	//t_data	img;

	vars.mlx_ptr = mlx_init();
	vars.mlx_win = mlx_new_window(vars.mlx_ptr, 720, 1080, "Hello world!");
	//img.img = mlx_new_image(mlx, 1920, 1080);
	//img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	//draw_line(&img, 5, 5, 20, 0x00FF0000);
	//mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_hook(vars.mlx_win, 2, 27, esc, &vars);
	mlx_hook(vars.mlx_win, 17, (1L << 17), mouse_click, &vars);
	mlx_loop(vars.mlx_ptr);
	
}
