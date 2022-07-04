/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 23:50:24 by Loui :)           #+#    #+#             */
/*   Updated: 2022/07/04 23:50:44 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# define RGB_RED = 0x00FF0000;
# define RGB_GREEN = 0x0000FF00;
# define RGB_BLUE = 0x000000FF;

# include <math.h>
# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>

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

typedef struct s_vars
{
	void	*mlx_ptr;
	void	*mlx_win;
}	t_vars;

/*utils*/
void	ft_putstr(char *s);
int		ft_strlen(char *str);
void	exit_msg(char *msg);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/*map_error*/
void	check_file_ext(char *filename);
// void ver_line(t_data *data, int x, int y, int len, int color);
// int		done(void);

#endif