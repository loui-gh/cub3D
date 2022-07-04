#include "raycast.h"

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

void ver_line(t_data *data, int x, int y, int len, int color)
{
	int		i;
	int		j;
	int		limit;

	i = 0;
	while (i < len && (j = y + 1) < limit)
	{
		y = j;
		put_pixel(data, x, y, color);
		i++;
	}
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, \
		&img.endian);
	draw_line(&img, 5, 5, 20, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
