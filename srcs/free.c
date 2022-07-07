/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 20:42:16 by jpfannku          #+#    #+#             */
/*   Updated: 2022/07/07 20:43:03 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

void	free_tex(t_textures *tex)
{
	if (tex->north)
		free(tex->north);
	if (tex->south)
		free(tex->south);
	if (tex->east)
		free(tex->east);
	if (tex->west)
		free(tex->west);
	// if (tex->ceiling)
	// 	free(tex->ceiling);
	// if (tex->floor)
	// 	free(tex->floor);
	free(tex);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while(map->map_arr[i])
	{
		free(map->map_arr[i]);
		i++;
	}
	free(map->map_arr);
	free(map);
}

void	free_vars_exit(char *msg, t_vars *vars)
{
	if (vars->tex)
		free_tex(vars->tex);
	if (vars->map)
		free_map(vars->map);
	exit_msg(msg);
}
