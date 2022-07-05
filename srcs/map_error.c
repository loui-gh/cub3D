/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 23:28:50 by Loui :)           #+#    #+#             */
/*   Updated: 2022/07/05 17:47:09 by jpfannku         ###   ########.fr       */
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
