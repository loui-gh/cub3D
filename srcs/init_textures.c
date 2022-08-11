/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 21:06:23 by Loui :)           #+#    #+#             */
/*   Updated: 2022/08/11 21:21:55 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

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

static void	rgb_normi(char *str, t_vars *vars, int floor, int ceiling)
{
	if (floor)
	{
		if (check_rgb_string(&str[2]) < 0)
		{
			free(str);
			free_vars_exit("Rgb string error\n", vars, EXIT_FAILURE);
		}
		else
			vars->tex->floor = to_hex(&str[2]);
	}
	else if (ceiling)
	{
		if (check_rgb_string(&str[2]) < 0)
		{
			free(str);
			free_vars_exit("Rgb string error\n", vars, EXIT_FAILURE);
		}
		else
			vars->tex->ceiling = to_hex(&str[2]);
	}
}

void	assign_tex_ptr(t_textures *ptr, char *holder, t_vars *vars)
{
	if (ptr->north == 0 && ft_strncmp("NO ", holder, 3) == 0)
		ptr->north = assign_tex(vars, &holder[3], holder);
	else if (ptr->south == 0 && ft_strncmp("SO ", holder, 3) == 0)
		ptr->south = assign_tex(vars, &holder[3], holder);
	else if (ptr->west == 0 && ft_strncmp("WE ", holder, 3) == 0)
		ptr->west = assign_tex(vars, &holder[3], holder);
	else if (ptr->east == 0 && ft_strncmp("EA ", holder, 3) == 0)
		ptr->east = assign_tex(vars, &holder[3], holder);
	else if (ptr->floor == 0 && ft_strncmp("F ", holder, 2) == 0)
		rgb_normi(holder, vars, 1, 0);
	else if (ptr->ceiling == 0 && ft_strncmp("C ", holder, 2) == 0)
		rgb_normi(holder, vars, 0, 1);
	else
	{
		free(holder);
		free_vars_exit("Error: Invalid texture\n", vars, EXIT_FAILURE);
	}
}
