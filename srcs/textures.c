/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 11:12:18 by jpfannku          #+#    #+#             */
/*   Updated: 2022/08/11 21:08:02 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

static void	free_norm(char *holder, t_vars *vars, char *exit)
{
	free(holder);
	free_vars_exit(exit, vars, EXIT_FAILURE);
}

t_data	*assign_tex(t_vars *vars, char *file, char *holder)
{
	t_data	*img;

	if (check_file_ext(file, ".xpm") < 0)
		free_norm(holder, vars, "xpm file expected\n");
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
	if (vars->tex->floor < 0 || vars->tex->ceiling < 0)
		free_vars_exit("Error: Invalid rgb colour\n", vars, EXIT_FAILURE);
}
