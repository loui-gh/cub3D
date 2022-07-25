/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 11:12:18 by jpfannku          #+#    #+#             */
/*   Updated: 2022/07/25 12:03:10 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

t_data	*assign_tex(t_vars *vars, char *file)
{
	t_data	*tex;

	if (check_file_ext(file, ".xpm") < 0)
		free_vars_exit("xpm file expected\n", vars, EXIT_FAILURE);
	tex = (t_data *)ft_calloc(sizeof(t_data), 1);
	if (!tex)
		free_vars_exit("Malloc error\n", vars, EXIT_FAILURE);
	file = skip_spaces(file);
	tex->img = mlx_xpm_file_to_image(vars->mlx_ptr, file, &tex->width, \
		&tex->height);
	if (tex->width != 64 || tex->height != 64)
		free_vars_exit("xpm size of 64x64 expected\n", vars, EXIT_FAILURE);
	return (tex);
}

void	check_textures(t_vars *vars)
{
	if (!vars->tex->north->img || !vars->tex->south->img \
		|| !vars->tex->east->img || !vars->tex->west->img)
		free_vars_exit("Error: Invalid texture\n", vars, EXIT_FAILURE);
	if (vars->tex->floor < 0 || vars->tex->ceiling < 0)
		free_vars_exit("Error: Invalid rgb colour\n", vars, EXIT_FAILURE);
}

void	assign_tex_ptr(t_textures *ptr, char *holder, t_vars *vars)
{
	if (ft_strncmp("NO ", holder, 3) == 0)
		ptr->north = assign_tex(vars, &holder[3]);
	else if (ft_strncmp("SO ", holder, 3) == 0)
		ptr->south = assign_tex(vars, &holder[3]);
	else if (ft_strncmp("WE ", holder, 3) == 0)
		ptr->west = assign_tex(vars, &holder[3]);
	else if (ft_strncmp("EA ", holder, 3) == 0)
		ptr->east = assign_tex(vars, &holder[3]);
	else if (ft_strncmp("F ", holder, 2) == 0)
		ptr->floor = to_hex(&holder[2]);
	else if (ft_strncmp("C ", holder, 2) == 0)
		ptr->ceiling = to_hex(&holder[2]);
	else
	{
		free(holder);
		free_vars_exit("Error: Invalid texture\n", vars, EXIT_FAILURE);
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
