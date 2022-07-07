/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 20:33:43 by jpfannku          #+#    #+#             */
/*   Updated: 2022/07/07 20:37:19 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

// error handling x2 here 
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

t_player	*init_player(int i, int j, char token)
{
	t_player	*player;

	player = (t_player *)malloc(sizeof(t_player));
	player->pos_y = i;
	player->pos_x = j;
    if (token == 'N') //direction x and y are where your head is pointing
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
	return (player);
}

