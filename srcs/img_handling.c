/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:06:47 by Loui :)           #+#    #+#             */
/*   Updated: 2022/07/07 17:16:08 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

/* identify and save all filepaths for textures in a struct 
@param 1: argv[1] of main, aka name of .cub file
*/

void	print_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		printf("%s\n", arr[i]);
		i++;
	}
}

void	map_width_height(t_map *map)
{
	int	longest;
	int	len;
	int	i;

	i = 0;
	longest = 0;
	len = 0;
	while (map->map_arr[i])
	{
		len = ft_strlen(map->map_arr[i]);
		if (len > longest)
			longest = len;
		i++;
	}
	map->width = len;
	map->height = i;
}

// error handling 2 instances here 
t_map	*create_map_array(int fd)
{
	char	buff[10000];
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	if (read(fd, buff, 10000) < 0)
		return (NULL);
	map->map_arr = ft_split(buff, '\n');
	return (map);
}

t_textures	*init_textures(int fd)
{
	t_textures	*ptr;
	int			i;
	char		*holder;

	ptr = (t_textures *)malloc(sizeof(t_textures));
	i = 0;
	while (i < 6)
	{
		holder = get_next_line(fd);
		while (ft_strlen(holder) < 2)
			holder = get_next_line(fd);
		if (ft_strncmp("NO ./img", holder, 8) == 0)
			ptr->north = ft_strdup(&holder[3]);
		else if (ft_strncmp("SO ./img", holder, 8) == 0)
			ptr->south = ft_strdup(&holder[3]);
		else if (ft_strncmp("WE ./img", holder, 8) == 0)
			ptr->west = ft_strdup(&holder[3]);
		else if (ft_strncmp("EA ./img", holder, 8) == 0)
			ptr->east = ft_strdup(&holder[3]);
		else if (ft_strncmp("F ", holder, 2) == 0)
			ptr->floor = to_hex(&holder[2]);
		else if (ft_strncmp("C ", holder, 2) == 0)
			ptr->ceiling = to_hex(&holder[2]);
		else
		{
			free(holder);
			free_tex(ptr);
			exit_msg("Error: invalid texture input\n");
		}
		free(holder);
		i++;
	}
	return (ptr);
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