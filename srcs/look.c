/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   look.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/25 17:41:20 by jpfannku          #+#    #+#             */
/*   Updated: 2022/07/25 17:50:07 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

int	look_left(t_vars *vars)
{
	char	*dir;
	int		i;

	dir = "NESW";
	i = 0;
	while (dir[i] && vars->player->token != dir[i])
		i++;
	if (i > 0)
		vars->player->token = dir[i - 1];
	else
		vars->player->token = dir[3];
	never_eat_soggy_weetbix(vars->player, vars->player->token);
	return (0);
}

int	look_right(t_vars *vars)
{
	char	*dir;
	int		i;

	dir = "NESW";
	i = 0;
	while (dir[i] && vars->player->token != dir[i])
		i++;
	if (i <= 2)
		vars->player->token = dir[i + 1];
	else
		vars->player->token = dir[0];
	never_eat_soggy_weetbix(vars->player, vars->player->token);
	return (0);
}
