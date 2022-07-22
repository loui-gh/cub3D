/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/18 11:12:18 by jpfannku          #+#    #+#             */
/*   Updated: 2022/07/22 11:16:01 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

t_data	*assign_tex(t_vars *vars, char *file)
{
	t_data	*tex;

	tex = (t_data *)ft_calloc(sizeof(t_data), 1);
	if (!tex)
		free_vars_exit("Malloc error\n", vars, EXIT_FAILURE);
	tex->img = mlx_xpm_file_to_image(vars->mlx_ptr, file, &tex->width, \
		&tex->height);
	return (tex);
}
