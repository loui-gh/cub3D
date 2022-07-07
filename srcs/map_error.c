/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 23:28:50 by Loui :)           #+#    #+#             */
/*   Updated: 2022/07/07 14:16:05 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

/* find start of map */
/* DA RULEZ
1st + last line only 1s
lines start and end with 1
0 cannot be preceded or followed by space (needs to b surrounded)
arr[i][j]
if char == 0, arr[i - 1][j] != ' ' && arr[i + 1][j]
only valid characters (1, 0, (N,S,W or E), space)
*/

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
	if (tex->ceiling)
		free(tex->ceiling);
	if (tex->floor)
		free(tex->floor);
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

void	check_file_ext(char *filename)
{
	int		i;

	i = 0;
	while (filename[i] && filename[i] != '.')
		i++;
	if (i == ft_strlen(filename))
		exit_msg("Wrong file extension, mate!\n");
	i++;
	if (ft_strncmp("cub", &filename[i], 4) != 0)
		exit_msg("Wrong file extension, mate!\n");
}

int	check_zeros(char **map, int i, int j, t_vars *vars)
{
	if (map[i][j + 1])
	{
		if (map[i][j + 1] == ' ')
			free_vars_exit("Map config error.\n", vars);
	}
	if (map[i][j - 1])
	{
		if (map[i][j - 1] == ' ')
			free_vars_exit("Map config error.\n", vars);
	}
	if (map[i + 1][j])
	{
		if (map[i + 1][j] == ' ')
			free_vars_exit("Map config error.\n", vars);
	}
	else
		free_vars_exit("Map config error.\n", vars);
	if (i != 0 && map[i - 1][j])
	{
		if (map[i - 1][j] == ' ')
			free_vars_exit("Map config error.\n", vars);
	}
	else
		free_vars_exit("Map config error.\n", vars);
	return (0);
}

void	check_map(char **map, t_vars *vars)
{
	int	i;
	int	j;
	int	token;
	int	flag;

	i = 0;
	token = 0;
	flag = 0;
	printf("beepboop");
	while (map[i])
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			token += ft_is_token(map[i][j], vars);
			if ( token == 1 && flag == 0)
			{
				flag = 1;
				vars->player = init_player(i, j, map[i][j]);
			}
			if (map[i][j] == '0')
				check_zeros(map, i, j, vars);
			j++;
		}
		i++;
	}
	if (token != 1)
		free_vars_exit("Invalid player input.\n", vars);
	printf("player x: %i y: %i, dirx: %i, diry: %i", vars->player->pos_x, vars->player->pos_y, vars->player->dir_x, vars->player->dir_y);
}
