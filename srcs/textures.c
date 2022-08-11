/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 11:12:18 by jpfannku          #+#    #+#             */
/*   Updated: 2022/08/11 14:32:03 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

void	free_norm(char *holder, t_vars *vars, char *exit)
{
	free(holder);
	free_vars_exit(exit, vars, EXIT_FAILURE);
}

t_data	*assign_tex(t_vars *vars, char *file, char *holder)
{
	t_data	*img;
	
	if (check_file_ext(file, ".xpm") < 0)
	{
		//this ft ^^ no longer works
		free_norm(holder, vars, "xpm file expected\n");
	}
		
	img = (t_data *)ft_calloc(sizeof(t_data), 1);
	if (!img)
		free_norm(holder, vars, "Malloc error\n");
	file = skip_spaces(file);
	img->img = mlx_xpm_file_to_image(vars->mlx_ptr, file, &img->width, \
		&img->height);
	if (img->img != 0x0)
		img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
			&img->line_length, &img->endian);
	if (img->width != 64 || img->height != 64)
	{
		if (img->img != 0x0)
			mlx_destroy_image(vars->mlx_ptr, img->img);
		free(img);
		free_norm(holder, vars, "Problem with xpm file\n");
	}
	return (img);
}

void	check_textures(t_vars *vars)
{
	if (!vars->tex->north->img || !vars->tex->south->img \
		|| !vars->tex->east->img || !vars->tex->west->img)
		free_vars_exit("1 Error: Invalid texture\n", vars, EXIT_FAILURE);
	//missing two frees before this point. What is allocated before here and not freed in 
	if (vars->tex->floor < 0 || vars->tex->ceiling < 0)
		free_vars_exit("Error: Invalid rgb colour\n", vars, EXIT_FAILURE);
}

void	assign_tex_ptr(t_textures *ptr, char *holder, t_vars *vars)
{
	if (ft_strncmp("NO ", holder, 3) == 0)
		ptr->north = assign_tex(vars, &holder[3], holder);
	else if (ft_strncmp("SO ", holder, 3) == 0)
		ptr->south = assign_tex(vars, &holder[3], holder);
	else if (ft_strncmp("WE ", holder, 3) == 0)
		ptr->west = assign_tex(vars, &holder[3], holder);
	else if (ft_strncmp("EA ", holder, 3) == 0)
		ptr->east = assign_tex(vars, &holder[3], holder);
	else if (ft_strncmp("F ", holder, 2) == 0)
	{
		if (check_rgb_string(&holder[2]) < 0)
		{
			free(holder);
			//close(fd);
			free_vars_exit("Rgb string error\n", vars, EXIT_FAILURE);
		}
		else
			ptr->floor = to_hex(&holder[2]);
	}
	else if (ft_strncmp("C ", holder, 2) == 0)
	{
		if (check_rgb_string(&holder[2]) < 0)
		{
			free(holder);
			free_vars_exit("Rgb string error\n", vars, EXIT_FAILURE);
		}
		else
			ptr->ceiling = to_hex(&holder[2]);
	}
	//two bytes lost before this point
	else
	{
		//printf("holder == |%s|\n", holder);
		free(holder);
		//close(fd);
		free_vars_exit("2 Error: Invalid texture\n", vars, EXIT_FAILURE);
	}
}

/*Assigns and creates img pointers to the xpm files, converts rgb to hex*/
void	init_textures(int fd, t_vars *vars)
{
	t_textures	*ptr;
	int			i;
	char		*holder;

	ptr = (t_textures *)ft_calloc(sizeof(t_textures), 1);
	vars->tex = ptr;
	i = 0;
	while (i < 6)
	{
		holder = get_next_line(fd);
		while (ft_strlen(holder) < 2)
			holder = get_next_line(fd);
		assign_tex_ptr(ptr, holder, vars);
		free(holder);
		i++;
	}
	check_textures(vars);
}
