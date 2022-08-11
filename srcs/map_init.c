/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 20:33:43 by jpfannku          #+#    #+#             */
/*   Updated: 2022/08/11 13:36:21 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

/* DESCRIPTION: searches for the LAST occurrence of the character c
* (an unsigned char) in the string pointed to by the argument str.
** RETURNS: last occurance + rest of string OR NULL if c not found in string
** *NOTE* c − is the character to be located. It is passed as its int promotion,
** but it is internally converted back to char
*/

int	ft_strrchr_mod(char *string, char c)
{
	int	i;

	i = ft_strlen(string);
	while (i > 0)
	{
		if (string[i] == c)
			return (i);
		i--;
	}
	return (-1);
}

int	ft_strnstr_mod(char *haystack, const char *needle, int n)
{
	int	i;
	int	j;

	i = 0;
	if (needle[i] == '\0')
		return (-1);
	while (haystack[i] != '\0' && i < n)
	{
		j = 0;
		while (haystack[i + j] == needle[j] && i + j < n)
		{
			if (needle[j + 1] == '\0')
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

void	gap_check(char *buffer, t_vars *vars)
{
	int	i;
	int	start_map;
	int	end_map;
	// char	*skinny_and_buff;

	i = 0;
	while (buffer[i] != '1' && buffer[i] != '\0')
	{
		if (buffer[i] == ' ' || buffer[i] == '	' || buffer[i] == '\n')
			i++;
		else
		{
			printf("poop!\n");
			free (buffer);
			free_vars_exit("unexpected char on road to map :)\n", vars, EXIT_FAILURE);
		}
	}
	start_map = i;
	end_map = ft_strrchr_mod(&buffer[start_map], '1');
	while (start_map < end_map)
	{
		if (buffer[start_map] == '\n' && buffer[start_map + 1] == '\n')
		{
			free (buffer);
			free_vars_exit("Space...so much space\n", vars, EXIT_FAILURE);
		}
		start_map++;
	}
	
	// skinny_and_buff = ft_strtrim(buffer, "\n");
	// printf("|%s|", skinny_and_buff);
	// i = ft_strrchr_mod(skinny_and_buff, '1');
	// if (ft_strnstr_mod(skinny_and_buff, "\n\n", i) == -1)
	// {
	// 	free(buffer);
	// 	free(skinny_and_buff);
	// 	free_vars_exit("1 Haha. You tried.\n", vars, EXIT_FAILURE);
	// }
	// else
	// 	free(skinny_and_buff);
}

void	create_map_array(int fd, t_vars *vars)
{
	char	*buff;
	t_map	*map;
	int		read_count;

	buff = ft_calloc(sizeof(char), 5000);
	read_count = read(fd, buff, 5000);
	close(fd);
	if (read_count < 0 || read_count >= 5000)
	{
		free(buff);
		free_vars_exit("Error reading map\n", vars, EXIT_FAILURE);
	}
	gap_check(buff, vars);
	map = (t_map *)ft_calloc(sizeof(t_map), 1);
	if (!map)
		free_vars_exit("Malloc error\n", vars, EXIT_FAILURE);
	vars->map = map;
	map->map_arr = ft_split(buff, '\n');
	free(buff);
	check_map(map->map_arr, vars);
	map_width_height(map);
	if (map->height < 3 || map->width < 3)
		free_vars_exit("2 Haha. You tried.\n", vars, EXIT_FAILURE);
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
		player->plane_x = 0.66;
		player->dir_y = -1;
	}
	if (token == 'S')
	{
		player->plane_x = -0.66;
		player->dir_y = 1;
	}
	if (token == 'E')
	{
		player->dir_x = 1;
		player->plane_y = 0.66;
	}
	if (token == 'W')
	{
		player->dir_x = -1;
		player->plane_y = -0.66;
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
