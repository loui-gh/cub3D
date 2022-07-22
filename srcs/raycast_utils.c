/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Loui :) <loflavel@students.42wolfsburg.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/22 22:18:37 by Loui :)           #+#    #+#             */
/*   Updated: 2022/07/22 22:18:46 by Loui :)          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

int	get_pix_colour(t_data *tex, int x, int y)
{
	if (x >= 0 && y >= 0 && x <= tex->width && x <= tex->height)
		return (*(int*)(tex->img + (4 * tex->width * y) + (4 * x)));
	else 
		return (0);
}