/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpfannku <jpfannku@student.42wolfsburg.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 17:26:33 by jpfannku          #+#    #+#             */
/*   Updated: 2022/07/07 20:41:24 by jpfannku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incl/raycast.h"

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i = write(2, &s[i], 1) + i;
	}
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && i < (n - 1))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/* DESCRIPTION: The strdup() function returns a pointer
* to a new string which is a duplicate of the string s.
* Memory for the new string is obtained with malloc(3),
* and can be freed with free(3). 
* RETURN VALUE: a pointer to the duplicated string,
* or NULL if insufficient memory was available*/
char	*ft_strdup(char *s)
{
	char	*dst_ptr;
	int		i;

	i = 0;
	dst_ptr = (char *)malloc(ft_strlen(s) + 1);
	if (dst_ptr == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		dst_ptr[i] = s[i];
		i++;
	}
	dst_ptr[i] = '\0';
	return (dst_ptr);
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
