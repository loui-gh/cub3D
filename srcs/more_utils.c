/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 12:47:39 by jpfannku          #+#    #+#             */
/*   Updated: 2022/08/02 12:53:13 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

#if __linux__

void	kill_disp(t_vars *vars)
{
	if (vars->mlx_ptr)
	{
		mlx_destroy_display(vars->mlx_ptr);
		free(vars->mlx_ptr);
	}
}

#else

void	kill_disp(t_vars *vars)
{
	(void) vars;
}

#endif

/* initialises a dbl-ptr int array using vars struct */

void	initarray(t_vars *ptr)
{
	int	i;

	i = 0;
	ptr->big_buff = (int **)malloc(sizeof(int *) * HEIGHT);
	if (!ptr->big_buff)
		free_vars_exit("Malloc fail", ptr, EXIT_FAILURE);
	while (i < HEIGHT)
	{
		ptr->big_buff[i] = (int *)malloc(WIDTH * sizeof(int));
		if (!ptr->big_buff[i])
			free_vars_exit("Malloc fail", ptr, EXIT_FAILURE);
		i++;
	}
	scrub_array(-1, ptr);
}

void	scrub_array(char c, t_vars *ptr)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			ptr->big_buff[y][x] = c;
			x++;
		}
		y++;
	}
}
