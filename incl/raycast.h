/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 23:50:24 by Loui :)           #+#    #+#             */
/*   Updated: 2022/07/22 12:06:23 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCAST_H
# define RAYCAST_H

# include <math.h>
# include <mlx.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# include <stdio.h>

# define WIDTH 1200
# define HEIGHT 900

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_data;

typedef struct s_map {
	int		width;
	int		height;
	char	**map_arr;
}	t_map;

typedef struct s_textures {
	t_data	*north;
	t_data	*south;
	t_data	*west;
	t_data	*east;
	int		floor;
	int		ceiling;
}	t_textures;

typedef struct s_player
{
	int		pos_x;
	int		pos_y;
	int		dir_x;
	int		dir_y;
	char	token;
}	t_player;

typedef struct s_vars
{
	void		*mlx_ptr;
	void		*mlx_win;
	t_textures	*tex;
	t_map		*map;
	t_player	*player;
	t_data		*img;
}	t_vars;

/*utils*/
void			ft_putstr(char *s);
int				ft_strlen(char *str);
void			exit_msg(char *msg, int exit_code);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*get_next_line(int fd);
char			**ft_split(char const *s, char c);
char			*ft_strdup(char *s);
int				ft_atoi(const char *str);
void			*ft_calloc(size_t n, size_t size);
char			*skip_spaces(char *line);
char			*ft_strtrim(char *s1, char *set);

/*memory*/
void			free_tex(t_textures *tex, t_vars *vars);
void			free_vars_exit(char *msg, t_vars *vars, int exit_code);
t_data			*assign_tex(t_vars *vars, char *file);

/*map build*/
void			check_file_ext(char *filename);
void			init_textures(int fd, t_vars *vars);
void			create_map_array(int fd, t_vars *vars);
void			check_map(char **map, t_vars *vars);
t_player		*init_player(int i, int j, char token);

/*mlx stuff*/
int				mouse_click(t_vars *vars);
int				esc(int keycode, t_vars *vars);
int				raycast(t_vars *vars);
void			verLine(int x, int y1, int y2, int color, t_data *data);
t_data			*floor_ceiling(t_vars *vars);
int				create_trgb(int t, int r, int g, int b);
int				to_hex(char *str);
int				raycast_tex(t_vars *vars);
void			put_pixel(t_data *data, int x, int y, int color);
int				player_move(int keycode, t_vars *vars);
int				go_forward(t_vars *vars);

/*testing*/
void			print_arr(char **arr);

#endif