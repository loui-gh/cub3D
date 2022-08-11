/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 21:14:29 by Loui :)           #+#    #+#             */
/*   Updated: 2022/08/11 21:15:37 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

char	*skip_spaces(char *line)
{
	int	x;

	x = 0;
	while (line[x] && (line[x] == ' ' || line[x] == '	'))
		x++;
	return (&line[x]);
}

int	kill_it(char **array)
{
	free_array(array);
	return (-1);
}

int	numbers_normi(int i, char **numbers)
{
	int		j;

	j = 0;
	while ((numbers[i][j] == ' ' || numbers[i][j] == '	') \
		&& numbers[i][j] != '\0')
		j++;
	while (ft_isdigit(numbers[i][j]) && numbers[i][j] != '\0')
		j++;
	while ((numbers[i][j] == ' ' || numbers[i][j] == '	') \
		&& numbers[i][j] != '\0')
		j++;
	return (j);
}

static int	check_numbers(char *str)
{
	char	**numbers;
	int		i;
	int		j;

	numbers = ft_split(str, ',');
	i = 0;
	while (numbers[i] != NULL)
	{
		j = 0;
		while (numbers[i][j] != '\0')
		{
			j = numbers_normi(i, numbers);
			if (ft_isdigit(numbers[i][j]))
				return (kill_it(numbers));
		}
		i++;
	}
	if (i != 3)
		return (kill_it(numbers));
	free_array(numbers);
	return (0);
}

int	check_rgb_string(char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if ((str[i] < '0' || str[i] > '9') && str[i] != ' ' \
			&& str[i] != ',' && str[i] != '	')
			return (-1);
		if (str[i] == ',')
			j++;
		i++;
	}
	if (j != 2)
		return (-1);
	if (check_numbers(str) == -1)
		return (-1);
	return (0);
}
