/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 23:28:50 by Loui :)           #+#    #+#             */
/*   Updated: 2022/07/05 18:50:25 by Loui :)          ###   ########.fr       */
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
		exit_msg("Wrong file extension, mate!\n");
	i++;

	if (ft_strncmp("cub", &filename[i], 4) != 0)
		exit_msg("Wrong file extension, mate!\n");
}