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

static int	ft_char_equals_set(char c, const char *set)
{
	while (*set)
		if (c == *set++ || c == '\n')
			return (0);
	return (1);
}

char	*ft_strtrim(char *s1, char *set)
{
	int		start;
	int		end;
	char	*new;

	if (!s1)
		return (0);
	if (!set)
		return (ft_strdup(s1));
	start = 0;
	end = ft_strlen(s1);
	while (ft_char_equals_set(s1[start], set) == 0)
		start++;
	if (start == ft_strlen(s1))
	{
		new = ft_strdup("");
		if (!new)
			return (0);
		else
			return (new);
	}
	while (ft_char_equals_set(s1[end - 1], set) == 0)
		end--;
	new = ft_substr(s1, start, end - start);
	return (new);
}

void	exit_msg(char *msg, int exit_code)
{
	ft_putstr(msg);
	exit(exit_code);
}
