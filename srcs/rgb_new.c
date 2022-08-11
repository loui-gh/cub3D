/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 11:23:12 by jpfannku          #+#    #+#             */
/*   Updated: 2022/08/11 11:38:01 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

int	create_trgb_new(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

char	*skip_spaces_new(char *line)
{
	int	x;

	x = 0;
	while (line[x] && (line[x] == ' ' || line[x] == '	'))
		x++;
	return (&line[x]);
}

int	check_num_new(char *num)
{
	int	i;

	i = 0;
	printf("num: %s\n", num);
	while (num[i] != '\0' && (num[i] == ' ' || num[i] == '	' || num[i] == '+'))
		i++;
	if (num[i] == '\0')
		return (-1);
	while (num[i] != '\0' && (num[i] >= '0' || num[i] <= '9'))
		i++;
	while (num[i] != '\0' && (num[i] == ' ' || num[i] == '	'))
		i++;
	if (num[i] != '\0')
		return (-1);
	return (1);
}

int	check_rgb_string_new(char *str)
{
	int		i;
	char	**numbers;

	i = 0;
	numbers = ft_split(str, ',');
	i = 0;
	while (numbers[i] != NULL)
		i++;
	if (i != 3)
	{
		free_array(numbers);
		return (-1);
	}
	if (check_num_new(numbers[0]) < 1 || check_num_new(numbers[1]) < 1 || \
		check_num_new(numbers[2]) < 1)
	{
		free_array(numbers);
		return (-1);
	}
	return (0);
}

/*converts rgb char string to hex for use with mlx functions
 -spaces
 -errors or invalid
*/
int	to_hex_new(char *str, t_init *init)
{
	int	i;
	int	r;
	int	g;
	int	b;

	if (check_rgb_string_new(str) < 0)
		free_init(init, "Rgb error\n", 1);
	str = skip_spaces_new(str);
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
		free_init(init, "Rgb error\n", 1);
	return (create_trgb_new(0x0, r, g, b));
}
