/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 20:42:16 by jpfannku          #+#    #+#             */
/*   Updated: 2022/07/19 20:57:30 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

void	destroy_free_img(t_data *img, t_vars *vars)
{
	if (img->img != 0x0)
		mlx_destroy_image(vars->mlx_ptr, img->img);
	free(img);
}

void	free_tex(t_textures *tex, t_vars *vars)
{
	if (tex->north)
		destroy_free_img(tex->north, vars);
	if (tex->south)
		destroy_free_img(tex->south, vars);
	if (tex->east)
		destroy_free_img(tex->east, vars);
	if (tex->west)
		destroy_free_img(tex->west, vars);
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

void	free_vars_exit(char *msg, t_vars *vars, int exit_code)
{
	if (vars->tex)
		free_tex(vars->tex, vars);
	if (vars->map)
		free_map(vars->map);
	if (vars->player)
		free(vars->player);
	if (vars->img)
		destroy_free_img(vars->img, vars); //this is a placeholder anyway 
	free(vars->mlx_ptr);
	free(vars);
	exit_msg(msg, exit_code);
}