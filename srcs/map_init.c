/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 20:33:43 by jpfannku          #+#    #+#             */
/*   Updated: 2022/07/27 18:07:46 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

void	create_map_array(int fd, t_vars *vars)
{
	char	*buff;
	t_map	*map;
	int		read_count;

	buff = ft_calloc(sizeof(char), 5000);
	map = (t_map *)ft_calloc(sizeof(t_map), 1);
	vars->map = map;
	if (!map)
	{
		close(fd);
		free_vars_exit("Malloc error\n", vars, EXIT_FAILURE);
	}
	read_count = read(fd, buff, 5000);
	if (read_count < 0 || read_count >= 5000)
	{
		close(fd);
		free_vars_exit("Error readind map\n", vars, EXIT_FAILURE);
	}
	map->map_arr = ft_split(buff, '\n');
	free(buff);
	close(fd);
	check_map(map->map_arr, vars);
	map_width_height(map);
	if (map->height < 3 || map->width < 3)
		free_vars_exit("Haha. You tried.\n", vars, EXIT_FAILURE);
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
	map->width = longest;
	map->height = i;
}

void	never_eat_soggy_weetbix(t_player *player, char token)
{
	if (token == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;
	}
	if (token == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
	}
	if (token == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;
	}
	if (token == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}
}

t_player	*init_player(int i, int j, char token)
{
	t_player	*player;

	player = (t_player *)ft_calloc(sizeof(t_player), 1);
	player->pos_y = i + 0.5;
	player->pos_x = j + 0.5;
	player->token = token;
	never_eat_soggy_weetbix(player, token);
	return (player);
}
