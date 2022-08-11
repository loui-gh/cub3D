/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   libft_utils_2.c									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: jpfannku <jpfannku@student.42wolfsburg.	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/07/22 11:53:28 by jpfannku		  #+#	#+#			 */
/*   Updated: 2022/07/22 11:54:18 by jpfannku		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../incl/raycast.h"

char	*ft_substr(char *s, int start, int len)
{
	char	*substring;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	substring = (char *)malloc(sizeof(char) * (len + 1));
	if (!substring)
		return (0);
	while (i < len && s[i + start] != '\0')
	{
		substring[i] = s[start + i];
		i++;
	}
	substring[i] = '\0';
	return (substring);
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
		x++;
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


static int
	ft_char_in_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char
	*ft_strtrim(char *s1, char *set)
{
	char	*str;
	size_t	i;
	size_t	start;
	size_t	end;

	start = 0;
	while (s1[start] && ft_char_in_set(s1[start], set))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_char_in_set(s1[end - 1], set))
		end--;
	str = (char*)malloc(sizeof(*s1) * (end - start + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (start < end)
		str[i++] = s1[start++];
	str[i] = 0;
	return (str);
}

void	exit_msg(char *msg, int exit_code)
{
	ft_putstr(msg);
	exit(exit_code);
}
