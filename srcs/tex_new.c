/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 10:51:25 by jpfannku          #+#    #+#             */
/*   Updated: 2022/08/11 11:21:46 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

void	free_init(t_init *init, char *msg, int exit)
{
	t_vars *vars;

	vars = init->vars;
	if(init->no)
		free(init->no);
	if(init->so)
		free(init->so);
	if(init->ea)
		free(init->ea);
	if(init->we)
		free(init->we);
	if(init->f)
		free(init->f);
	if(init->c)
		free(init->c);
	//close(fd);
	free(init);
	if (exit == 1)
		free_vars_exit(msg, vars, EXIT_FAILURE);
}

t_data	*assign_tex_new(t_init *init, char *file)
{
	t_data	*img;
	
	if (check_file_ext(file, ".xpm") < 0)
		free_init(init, "Expected xpm file\n", 1);
	img = (t_data *)ft_calloc(sizeof(t_data), 1);
	if (!img)
		free_init(init, "Malloc error\n", 1);
	file = skip_spaces(file);
	img->img = mlx_xpm_file_to_image(init->vars->mlx_ptr, file, &img->width, \
		&img->height);
	if (img->img != 0x0)
		img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
			&img->line_length, &img->endian);
	if (img->width != 64 || img->height != 64)
	{
		if (img->img != 0x0)
			mlx_destroy_image(init->vars->mlx_ptr, img->img);
		free(img);
		free_init(init, "Xpm texture error\n", 1);
	}
	return (img);
}

void	assign_tex_ptr_new(t_init *init)
{
	init->vars->tex = (t_textures *)ft_calloc(sizeof(t_textures), 1);
	init->vars->tex->north = assign_tex_new(init, init->no);
	init->vars->tex->south = assign_tex_new(init, init->so);
	init->vars->tex->east = assign_tex_new(init, init->ea);
	init->vars->tex->west = assign_tex_new(init, init->we);
	//init->vars->tex->floor = assign_tex_new(init, init->f); //check rgb
	//init->vars->tex->ceiling = assign_tex_new(init, init->c);
}

void	tex_char(char *holder, t_init *init)
{
	if (ft_strncmp("NO ", holder, 3) == 0 && init->no != 0)
		init->no = holder;
	else if (ft_strncmp("SO ", holder, 3) == 0 && init->so != 0)
		init->so = holder;
	else if (ft_strncmp("WE ", holder, 3) == 0 && init->we != 0)
		init->we = holder;
	else if (ft_strncmp("EA ", holder, 3) == 0 && init->ea != 0)
		init->ea = holder;
	else if (ft_strncmp("F ", holder, 2) == 0 && init->f != 0)
		init->f = holder;
	else if (strncmp("C ", holder, 2) == 0 && init->c != 0)
		init->c = holder;
	else 
		free_init(init, "Texture format error\n", 1);
}

void	init_textures_new(t_init *init)
{
	int			i;
	char		*holder;

	i = 0;
	while (i < 6)
	{
		holder = get_next_line(init->fd);
		while (ft_strlen(holder) < 2)
			holder = get_next_line(init->fd);
		tex_char(holder, init);
		i++;
	}
	//check if there are more lines after the initial 6?
	assign_tex_ptr_new(init);
	free_init(init, "", 0);
}