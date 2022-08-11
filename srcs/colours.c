/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colours.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 12:33:58 by Loui :)           #+#    #+#             */
/*   Updated: 2022/08/11 12:34:36 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"


static int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

/*converts rgb char string to hex for use with mlx functions
*/
int	to_hex(char *str)
{
	int	i;
	int	r;
	int	g;
	int	b;

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
