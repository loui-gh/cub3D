/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 19:06:47 by Loui :)           #+#    #+#             */
/*   Updated: 2022/08/10 21:40:59 by Loui :)          ###   ########.fr       */
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
	char	**numbers;

	i = 0;

	while (str[i] != '\0')
	{
		if ((str[i] >= '0' && str[i] <= '9') || str[i] == ' ' || str[i] == '	')
			i++;
		else
		{
			printf("sup!\n");
			return (-1);
		}
	}
	numbers = ft_split(str, ',');
	i = 0;
	while (numbers[i] != NULL)
		i++;
	if (i != 3)
		return (-1);
	free_array(numbers);
	// while (numbers[i])
	// {
	// 	j = 0;
	// 	while (numbers[i][j] != '\0')
	// 	{
	// 		{
	// 			free_array(numbers);
	// 			return (-1);
	// 		}
	// 		if (numbers[i][j] == ' ' && (numbers[i][j] >= '0' || 
	// 			numbers[i][j] <= '9'))
	// 		{
	// 			write(1, "5\n", 2);
	// 			free_array(numbers);
	// 			return (-1);
	// 		}
	// 		j++;
	// 	}
	// 	i++;
	// }
	return (0);
}

/*converts rgb char string to hex for use with mlx functions
 -spaces
 -errors or invalid
*/
int	to_hex(char *str, t_vars *vars)
{
	int	i;
	int	r;
	int	g;
	int	b;

	if (check_rgb_string(str) < 0)
	{
		printf("poop!\n");
		free_vars_exit("rgb error\n", vars, EXIT_FAILURE);
		return (-1);
	}
		
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
