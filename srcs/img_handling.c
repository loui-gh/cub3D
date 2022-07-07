/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_handling.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:06:47 by Loui :)           #+#    #+#             */
/*   Updated: 2022/07/07 20:38:51 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	to_hex(char *str) //major error handling needed here 
{
	int	i;
	int	r;
	int	g;
	int	b;
	
	i = 0;
	r = ft_atoi(str);
	while(str[i] && str[i] != ',')
		i++;
	i++;
	g = ft_atoi(&str[i]);
	while(str[i] && str[i] != ',')
		i++;
	i++;
	b = ft_atoi(&str[i]);
	if (r < 0 || g < 0 || b < 0)
		exit_msg("add free here");
	return (create_trgb(0x0, r, g, b));
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
