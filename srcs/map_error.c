/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 23:28:50 by Loui :)           #+#    #+#             */
/*   Updated: 2022/07/06 20:27:16 by Loui :)          ###   ########.fr       */
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

int	check_zeros(char **map, int i, int j)
{
	if (map[i][j + 1])
	{
		if (map[i][j + 1] == ' ')
			exit_msg("Map config error.\n");
	}
	if (map[i][j - 1])
	{
		if (map[i][j - 1] == ' ')
			exit_msg("Map config error.\n");
	}
	if (map[i + 1][j])
	{
		if (map[i + 1][j] == ' ')
			exit_msg("Map config error.\n");
	}
	else
		exit_msg("Map config error.\n");
	if (i != 0 && map[i - 1][j])
	{
		if (map[i - 1][j] == ' ')
			exit_msg("Map config error.\n");
	}
	else
		exit_msg("Map config error.\n");
	return (0);
}

void	check_map(char **map)
{
	int	i;
	int	j;
	int	token;

	i = 0;
	token = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			token += ft_is_token(map[i][j]);
			if (map[i][j] == '0')
				check_zeros(map, i, j);
			j++;
		}
		i++;
	}
	if (token != 1)
		exit_msg("Invalid player input.\n");
	printf("token = %d\n", token);
}
