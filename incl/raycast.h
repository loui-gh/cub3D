/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 23:50:24 by Loui :)           #+#    #+#             */
/*   Updated: 2022/07/25 23:13:17 by Loui :)          ###   ########.fr       */
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

typedef struct s_raycast
{
	float	ray_dir_x;
	float	ray_dir_y;
	float	side_dist_x;
	float	side_dist_y;
	float	perp_wall_dist;
	int		map_x;
	int		map_y;
	int		hit;
	int		side;
	int		draw_start;
	int		draw_end;
	double	wall_x;
	int		tex_x;
	double	step;
	double	tex_pos;
	int		step_x;
	int		step_y;
}	t_raycast;

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
	int		collide;
	char	token;
}	t_player;

typedef struct s_vars
{
	void		*mlx_ptr;
	void		*mlx_win;
	int			**big_buff;
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
int				check_file_ext(char *filename, char *file_ext);
void			init_textures(int fd, t_vars *vars);
void			create_map_array(int fd, t_vars *vars);
void			check_map(char **map, t_vars *vars);
t_player		*init_player(int i, int j, char token);

/*mlx stuff*/
int				mouse_click(t_vars *vars);
int				esc(int keycode, t_vars *vars);
int				raycast(t_vars *vars);
t_data			*floor_ceiling(t_vars *vars);
int				create_trgb(int t, int r, int g, int b);
int				to_hex(char *str);
void			put_pixel(t_data *data, int x, int y, int color);
int				player_move(int keycode, t_vars *vars);
int				go_forward(t_vars *vars);

/*testing*/
void			print_arr(char **arr);

/*raycasting*/
int				get_pix_colour(t_data *tex, int x, int y);
int				raycast_tex(t_vars *vars);
void			initarray(t_vars *ptr);
void			scrub_array(char c, t_vars *ptr);
void			write_buffer_to_img(t_data *img, int **buffer);
void			fill_buffer(int x, t_raycast *ray, t_vars *ptr);

/*map*/
void			map_width_height(t_map *map);
#endif