/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 23:50:24 by Loui :)           #+#    #+#             */
/*   Updated: 2022/07/06 15:23:31 by jpfannku         ###   ########.fr       */
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
# include <fcntl.h>

# include <stdio.h>

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_map {
	int		width;
	int		height;
	char	**map_arr;
}	t_map;

typedef struct s_textures {
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*floor;
	char	*ceiling;
}	t_textures;

typedef struct s_player
{
	int	pos_x;
	int	pos_y;
	int	dir_x;
	int	dir_y;
}	t_player;

typedef struct s_vars
{
	void		*mlx_ptr;
	void		*mlx_win;
	t_textures	*tex;
	t_map		*map;
	t_player	*player;
}	t_vars;

/*utils*/
void			ft_putstr(char *s);
int				ft_strlen(char *str);
void			exit_msg(char *msg);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*get_next_line(int fd);
char			**ft_split(char const *s, char c);
char			*ft_strdup(char *s);
void			free_tex(t_textures *tex);
void			free_vars_exit(char *msg, t_vars *vars);
/*map_error*/
void			check_file_ext(char *filename);
t_textures		*init_textures(int fd);
t_map			*create_map_array(int fd);
void			check_map(char **map, t_vars *vars);
int				check_zeros(char **map, int i, int j, t_vars *vars);
int				ft_is_token(int c, t_vars *vars);
t_player		*init_player(int i, int j, char token);
/*mlx stuff*/
int				mouse_click(t_vars *vars);
int				esc(int keycode, t_vars *vars);
int 			raycast(t_vars *vars);

/*testing*/
void			print_arr(char **arr);

// void ver_line(t_data *data, int x, int y, int len, int color);

#endif