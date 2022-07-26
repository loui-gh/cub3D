/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 20:33:43 by jpfannku          #+#    #+#             */
/*   Updated: 2022/07/26 13:31:45 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

void	create_map_array(int fd, t_vars *vars)
{
	char	buff[10000];
	t_map	*map;
	int		i;

	i = 0;
	map = (t_map *)ft_calloc(sizeof(t_map), 1);
	vars->map = map;
	if (!map)
	{
		close(fd);
		free_vars_exit("Malloc error\n", vars, EXIT_FAILURE);
	}
	if (read(fd, buff, 10000) < 0)
	{
		close(fd);
		free_vars_exit("Error readind map\n", vars, EXIT_FAILURE);
	}
	while (buff[i] == '\n')
		i++;
	map->map_arr = ft_split(&buff[i], '\n');
	close(fd);
	check_map(map->map_arr, vars);
	map_width_height(map);
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
	player->pos_y = i;
	player->pos_x = j;
	player->token = token;
	never_eat_soggy_weetbix(player, token);
	return (player);
}
