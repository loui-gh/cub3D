/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:06:47 by Loui :)           #+#    #+#             */
/*   Updated: 2022/07/22 11:22:51 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	to_hex(char *str)
{
	int	i;
	int	r;
	int	g;
	int	b;

	i = 0;
	r = ft_atoi(str);
	while (str[i] && str[i] != ',')
		i++;
	i++;
	g = ft_atoi(&str[i]);
	while (str[i] && str[i] != ',')
		i++;
	i++;
	b = ft_atoi(&str[i]);
	if (r < 0 || g < 0 || b < 0)
		return (-1);
	return (create_trgb(0x0, r, g, b));
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
