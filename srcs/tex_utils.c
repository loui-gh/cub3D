/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:06:47 by Loui :)           #+#    #+#             */
/*   Updated: 2022/08/10 20:31:40 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

char	*skip_spaces(char *line)
{
	int	x;

	x = 0;
	while (line[x] && (line[x] == ' ' || line[x] == '	'))
		x++;
	return (&line[x]);
}

int	check_rgb_string(char *str)
{
	int		i;
	int		j;
	char	**numbers;

	numbers = ft_split(str, ',');
	i = 0;
	while (numbers[i] != NULL)
		i++;
	if (i != 2)
	{
		free_array(numbers);
		return (-1);
	}
	i = 0;
	j = 0;

	i = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != ' ' \
		&& str[i] != ',' && str[i] != '	')
			return (-1);
		i++;
	}
	return (0);
}

/*converts rgb char string to hex for use with mlx functions
 -spaces
 -errors or invalid
*/
int	to_hex(char *str)
{
	int	i;
	int	r;
	int	g;
	int	b;

	if (check_rgb_string(str) < 0)
		return (-1);
	str = skip_spaces(str);
	i = 0;
	r = ft_atoi(str);
	while (str[i] && str[i] != ',')
		i++;
	i++;
	g = ft_atoi(&str[i]);
	while (str[i] && str[i] != ',')
		i++;
	i++;
	b = ft_atoi(&str[i]);
	if (r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255)
		return (-1);
	return (create_trgb(0x0, r, g, b));
}
