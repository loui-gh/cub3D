/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 23:38:56 by Loui :)           #+#    #+#             */
/*   Updated: 2022/08/11 11:48:45 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

char	*get_next_line(int fd)
{
	char	line[10000];
	char	*buf;
	char	*trimmed;
	int		test;

	buf = line;
	test = 0;
	while (read(fd, buf, 1) > 0 && *buf++ != '\n')
		test++;
	if (buf > line)
	{
		*buf = 0;
		trimmed = ft_strtrim(line, " 	\n");
		return (trimmed);
	}
	else
		return (NULL);
}
