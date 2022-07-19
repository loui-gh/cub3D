/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 23:38:56 by Loui :)           #+#    #+#             */
/*   Updated: 2022/07/19 10:40:30 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

void	exit_msg(char *msg, int exit_code)
{
	ft_putstr(msg);
	exit(exit_code);
}

char	*get_next_line(int fd)
{
	char	line[10000];
	char	*buf;
	int		test;

	buf = line;
	test = 0;
	while (read(fd, buf, 1) > 0 && *buf++ != '\n')
		test++;
	if (buf > line)
	{
		*buf = 0;
		return (ft_strdup(line));
	}
	else
		return (NULL);
}
