/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:57:27 by jpfannku          #+#    #+#             */
/*   Updated: 2022/07/07 17:26:13 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

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

int	ft_atoi(const char *str)
{
	int	val;
	int	x;
	int	neg;

	val = 0;
	x = 0;
	neg = 1;
	while ((str[x] >= 9 && str[x] <= 13) || str[x] == 32)
	{
		x++;
	}
	if (str[x] == '-')
	{
		neg = -1;
		x++;
	}
	else if (str[x] == '+')
		x++;
	while (str[x] >= '0' && str[x] <= '9')
	{
		val = val * 10 + str[x] - 48;
		x++;
	}
	return (val * neg);
}
