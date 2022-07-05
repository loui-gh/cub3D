/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:06:47 by Loui :)           #+#    #+#             */
/*   Updated: 2022/07/05 14:36:57 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

/* identify and save all filepaths for textures in a struct 
@param 1: argv[1] of main, aka name of .cub file
*/

void	init_textures(char *map)
{
	t_textures	*ptr;
	int			fd;
	int			i;
	char		*holder;

	ptr = (t_textures *)malloc(sizeof(t_textures));
	check_file_ext(map);
	fd = open(map, O_RDONLY);
	if (fd < 0)
		exit_msg("Cannot read from file\n");
	i = 0;
	while (i < 6)
	{
		holder = get_next_line(fd);
		while (ft_strlen(holder) < 2)
			holder = get_next_line(fd);
		if (ft_strncmp("NO ./img", holder, 8) == 0)
			ptr->north = &holder[3];
		else if (ft_strncmp("SO ./img", holder, 8) == 0)
			ptr->south = &holder[3];
		else if (ft_strncmp("WE ./img", holder, 8) == 0)
			ptr->west = &holder[3];
		else if (ft_strncmp("EA ./img", holder, 8) == 0)
			ptr->east = &holder[3];
		else if (ft_strncmp("F ", holder, 2) == 0)
			ptr->floor = &holder[2];
		else if (ft_strncmp("C ", holder, 2) == 0)
			ptr->ceiling = &holder[2];
		else
			exit_msg("Error: invalid texture input\n");
		i++;
	}
	printf("NO: %sSO: %sEA: %sWE: %sF:%sC:%s", ptr->north, ptr->south, ptr->east, ptr->west, ptr->floor, ptr->ceiling);
}

/*void	create_map_array(t_vars *vars, char *map_path)
{
	ssize_t		rc;
	int			fd;

	vars->buf = ft_calloc(sizeof(char), 1000);
	fd = open(map_path, O_RDONLY);
	//if (fd == -1) print error msg
	rc = read(fd, vars->buf, 1000);
	if (rc < 1)
	{
		ft_free(vars);
		close(fd);
		exit(EXIT_FAILURE);
	}
	vars->map->ptr_map = ft_split(vars->buf, '\n');
	if (vars->map->ptr_map == NULL)

}*/