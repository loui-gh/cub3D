/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   raycast.c									  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/07/06 15:12:06 by jpfannku		  #+#	#+#			 */
/*   Updated: 2022/08/02 19:17:54 by Loui :)		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../incl/raycast.h"

/* //length of ray from one x or y-side to next x or y-side */

/*
void	set_y_vectors(t_raycast *ray, t_vars *vars)
{
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = ((float)(sqrt(1 + (ray->dir_x * \
		ray->dir_x) / (ray->dir_y * ray->dir_y)))) * \
		(vars->player->pos_y - ray->map_y);
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = ((float)(sqrt(1 + (ray->dir_x * \
		ray->dir_x) / (ray->dir_y * ray->dir_y)))) * \
		(ray->map_y - vars->player->pos_y + 1.0);
	}
}


void	set_x_vectors(t_raycast *ray, t_vars *vars)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = ((float)(sqrt(1 + (ray->dir_y * \
		ray->dir_y) / (ray->dir_x * ray->dir_x)))) * \
		(vars->player->pos_x - ray->map_x);
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = ((float)(sqrt(1 + (ray->dir_y * \
		ray->dir_y) / (ray->dir_x * ray->dir_x)))) * \
		(ray->map_x - vars->player->pos_x + 1.0);
	}
}
*/

//why is the calc of perp_wall so different here from tutorial?
void	find_wall_coord(t_raycast *ray, t_vars *vars)
{
	if (ray->side == 0)
		ray->perp_wall_dist =  (ray->map_x - vars->player->pos_x + \
			(1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->perp_wall_dist = (ray->map_y - vars->player->pos_y + \
			(1 - ray->step_y) / 2) / ray->dir_y;
	ray->draw_start = -(HEIGHT / ray->perp_wall_dist) / 2 + HEIGHT / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = (HEIGHT / ray->perp_wall_dist) / 2 + HEIGHT / 2;
	if (ray->draw_end >= HEIGHT)
		ray->draw_end = HEIGHT - 1;
	if (ray->side == 0)
		ray->wall_x = vars->player->pos_y + \
			ray->perp_wall_dist * ray->dir_y;
	else
		ray->wall_x = vars->player->pos_x + \
			ray->perp_wall_dist * ray->dir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)vars->tex->north->height);
	if (ray->side == 0 && ray->dir_x > 0)
		ray->tex_x = vars->tex->north->height - ray->tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		ray->tex_x = vars->tex->north->height - ray->tex_x - 1;
}



/* DDA or "Digital Differential Analysis". DDA is a fast algorithm 
typically used on square grids to find which squares a line hits 
(for example to draw a line on a screen, which is a grid of square pixels). 
So we can also use it to find which squares of the map our ray hits, 
and stop the algorithm once a square that is a wall is hit. */

void	dda(t_raycast *ray, t_vars *vars)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		//check if ray has hit a wall
		if (vars->map->map_arr[(int)ray->map_y][(int)ray->map_x] == '1')
			hit = 1;
	}
}


void	raycast(t_raycast *ray, t_vars *vars)
{
	int	x;

	x = 0;
	while (x < WIDTH)
	{
		//CHANGED
		ray->camera_x = 2 * x / (double)WIDTH - 1;
		ray->dir_x = vars->player->dir_x + vars->player->plane_x * ray->camera_x;
		ray->dir_y = vars->player->dir_y + vars->player->plane_y * ray->camera_x;
		
		 //(which box of the map we're in)
		//changed map_x and y to ints in header file
		ray->map_x = (int)vars->player->pos_x; //how does this change??
		ray->map_y = (int)vars->player->pos_y;

	//length of ray from one x or y-side to next x or y-side
		ray->delta_dist_x = sqrt(1 + (ray->dir_y * ray->dir_y) / (ray->dir_x * ray->dir_x));
		ray->delta_dist_y = sqrt(1 + (ray->dir_x * ray->dir_x) / (ray->dir_y * ray->dir_y));

	//calculate step and initialise sideDist. Vectors/rays (delta x/y) need to be initialised before this part
		if (ray->dir_x < 0)
		{
			ray->step_x = -1;
			ray->side_dist_x = (vars->player->pos_x - ray->map_x) * ray->delta_dist_x; //now correctly initalised :)
		}
		else
		{
			ray->step_x = 1;
			ray->side_dist_x = (ray->map_x + 1.0 - vars->player->pos_x) * ray->delta_dist_x;
		}
		if (ray->dir_y < 0)
		{
			ray->step_y = -1;
			ray->side_dist_y =	(vars->player->pos_y - ray->map_y) * ray->delta_dist_y;
		}
		else
		{
			ray->step_y = 1;
			ray->side_dist_y = (ray->map_y + 1.0 - vars->player->pos_y) * ray->delta_dist_y;
		}

		dda(ray, vars);

		//Calculate distance of perpendicular ray
		if (ray->side == 0)
			ray->perp_wall_dist = ray->side_dist_x - ray->delta_dist_x;
		else
			ray->perp_wall_dist = ray->side_dist_y - ray->delta_dist_y;

		int line_height = (int)(HEIGHT / ray->perp_wall_dist);
		ray->draw_start = -line_height / 2 + HEIGHT / 2;
		if (ray->draw_start < 0)
			ray->draw_start = 0;
		
		ray->draw_end = line_height / 2 + HEIGHT / 2;
		if(ray->draw_end >= HEIGHT) 
			ray->draw_end = HEIGHT - 1;


		// if (ray->dir_x == 0)
		// 	ray->delta_dist_x = 1e30;
		// else
		// 	ray->delta_dist_x = fabs(1 / ray->dir_x);
		// if (ray->dir_y == 0)
		// 	ray->delta_dist_y = 1e30;
		// else
		// 	ray->delta_dist_y = fabs(1 / ray->dir_y);
		
		//calculate step and side dist
		//replaces set_x/y_vectors fts --wtf did that sqrt ft come from??
		
		//set_x_vectors(ray, vars);
		//set_y_vectors(ray, vars);
		
		 //Calculate distance of perpendicular ray
		//find_wall_coord(ray, vars);
		

		
      //texturing calculations
      //int texNum = worldMap[mapX][mapY] - 1; //1 subtracted from it so that texture 0 can be used!

      //calculate value of wallX -- where wall was hit
      
      if (ray->side == 0)
	  	ray->wall_x = vars->player->pos_y + ray->perp_wall_dist * ray->dir_y;
      else
		ray->wall_x = vars->player->pos_x + ray->perp_wall_dist * ray->dir_x;
	  ray->wall_x -= floor(ray->wall_x);

      //tex_x coordinate of the texture. this coordinate will remain the same, 
	  //because we stay in the same vertical stripe of the screen
		ray->tex_x = (int)(ray->wall_x * (double)tex_width);
		if(ray->side == 0 && ray->dir_x > 0)
			ray->tex_x = tex_width - ray->tex_x - 1;
		if(ray->side == 1 && ray->dir_y < 0)
			ray->tex_x = tex_width - ray->tex_x - 1;

		// fill_buffer(x, ray, vars);

            // How much to increase the texture coordinate per screen pixel
      double step = 1.0 * tex_height / line_height;
      // Starting texture coordinate
      ray->tex_pos = (ray->draw_start - HEIGHT / 2 + line_height / 2) * step;

	//fill_buffer ft
	  int y = ray->draw_start;
	  int tex_y;
      while(y < ray->draw_end)
      {
        // Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
        tex_y = (int)ray->tex_pos &(tex_height - 1);
        ray->tex_pos += step;
        if (ray->side == 0 && vars->player->pos_x < ray->map_x)
			vars->big_buff[y][x] = \
				get_pix_colour(vars->tex->west, ray->tex_x, tex_y);
		else if (ray->side == 0 && vars->player->pos_x > ray->map_x)
			vars->big_buff[y][x] = \
				get_pix_colour(vars->tex->east, ray->tex_x, tex_y);
		else if (ray->side == 1 && vars->player->pos_y < ray->map_y)
			vars->big_buff[y][x] = \
				get_pix_colour(vars->tex->north, ray->tex_x, tex_y);
		else
			vars->big_buff[y][x] = \
				get_pix_colour(vars->tex->south, ray->tex_x, tex_y);
		y++;
      }


		/*
		ray->step = 1.0 * vars->tex->north->height / \
				(int)(HEIGHT / ray->perp_wall_dist);
		ray->tex_pos = (ray->draw_start - HEIGHT / 2 + \
				(int)(HEIGHT / ray->perp_wall_dist) / 2) * ray->step;
		*/
		x++;
	}
}

int	render_image(t_vars *vars)
{
	// int			m;
	t_raycast	*ray;
	t_data		*fl_c;

	// m = 0;
	fl_c = floor_ceiling(vars);
	ray = (t_raycast *)ft_calloc(sizeof(t_raycast), 1);
	// while (m < 1)
	// {
	raycast(ray, vars); 
	// 	m++;
	// }
	free(ray);
	write_buffer_to_img(fl_c, vars->big_buff);
	mlx_put_image_to_window(vars->mlx_ptr, vars->mlx_win, fl_c->img, 0, 0);
	vars->img = fl_c;
	scrub_array(-1, vars);
	return (0);
}
