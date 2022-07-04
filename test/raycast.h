#ifndef RAYCAST_H
# define RAYCAST_H

# define RGB_RED = 0x00FF0000;
# define RGB_GREEN = 0x0000FF00;
# define RGB_BLUE = 0x000000FF;

#include <math.h>
#include <mlx.h>

typedef struct s_colour {
	int		bal;
}				t_colour;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

void ver_line(t_data *data, int x, int y, int len, int color);
int		done(void);

#endif