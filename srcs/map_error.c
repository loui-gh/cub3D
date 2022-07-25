/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 23:28:50 by Loui :)           #+#    #+#             */
/*   Updated: 2022/07/25 16:01:40 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

void	check_file_ext(char *filename)
{
	int		i;

	i = 0;
	while (filename[i] && filename[i] != '.')
		i++;
	if (i == ft_strlen(filename))
		exit_msg("Wrong file extension, mate!\n", EXIT_FAILURE);
	i++;
	if (ft_strncmp("cub", &filename[i], 4) != 0)
		exit_msg("Wrong file extension, mate!\n", EXIT_FAILURE);
}

int	ft_is_token(int c, t_vars *vars)
{
	if (c != '1' && c != '0' && c != ' ' && c != 'N' \
			&& c != 'S' && c != 'W' && c != 'E')
		free_vars_exit("Map config error.\n", vars, EXIT_FAILURE);
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	else
		return (0);
}

/* There can be no space next to a zero in the map,
otherwise there is a 'hole' in the game. This function
checks for that.*/
void	check_zeros_normi(char **map, int i, int j, t_vars *vars)
{
	if (i != 0 && map[i - 1][j])
	{
		if (map[i - 1][j] == ' ')
			free_vars_exit("Map config error.\n", vars, EXIT_FAILURE);
	}
	else
		free_vars_exit("Map config error.\n", vars, EXIT_FAILURE);
}

void	check_zeros(char **map, int i, int j, t_vars *vars)
{
	if (map[i][j + 1])
	{
		if (map[i][j + 1] == ' ' || map[i][j + 1] == '\n')
			free_vars_exit("Map config error.\n", vars, EXIT_FAILURE);
	}
	else
		free_vars_exit("Holy wall.\n", vars, EXIT_FAILURE);
	if (map[i][j - 1])
	{
		if (map[i][j - 1] == ' ')
			free_vars_exit("Map config error.\n", vars, EXIT_FAILURE);
	}
	if (map[i + 1][j])
	{
		if (map[i + 1][j] == ' ')
			free_vars_exit("Map config error.\n", vars, EXIT_FAILURE);
	}
	else
		free_vars_exit("Map config error.\n", vars, EXIT_FAILURE);
	check_zeros_normi(map, i, j, vars);
}

/* check map for invalid tokens (i.e. not 0, etc.)
also check walls
*/
void	check_map(char **map, t_vars *vars)
{
	int	i;
	int	j;
	int	player;

	i = 0;
	player = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j] != '\0')
		{
			player += ft_is_token(map[i][j], vars);
			if (player == 1 && !vars->player)
				vars->player = init_player(i, j, map[i][j]);
			if (map[i][j] == '0')
				check_zeros(map, i, j, vars);
			j++;
		}
		i++;
	}
	if (player != 1)
		free_vars_exit("Invalid player input.\n", vars, EXIT_FAILURE);
}
