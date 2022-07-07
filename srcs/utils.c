/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 23:38:56 by Loui :)           #+#    #+#             */
/*   Updated: 2022/07/07 20:41:16 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

void	exit_msg(char *msg)
{
	ft_putstr(msg);
	exit(EXIT_FAILURE);
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
