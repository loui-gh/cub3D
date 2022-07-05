/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   ft_split.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: jpfannku <jpfannku@student.42wolfsburg.	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/07/05 14:59:06 by jpfannku		  #+#	#+#			 */
/*   Updated: 2022/07/05 14:59:25 by jpfannku		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../incl/raycast.h"

static int	ft_count_strings(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] != c && s[i])
			i++;
	}
	return (count);
}

static int	ft_string_len(char const *s, char c)
{
	int	len;

	len = 0;
	while (s[len] != 0 && s[len] != c)
		len++;
	return (len);
}

static char	*ft_create_string(const char *s, size_t n)
{
	char	*dest;
	size_t	i;

	i = 0;
	dest = malloc((n + 1) * sizeof(char *));
	if (!dest)
		return (NULL);
	while (i < n)
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	size_t	i;
	size_t	string;

	i = 0;
	if (s == 0)
		return (NULL);
	string = ft_count_strings(s, c);
	array = malloc((string + 1) * sizeof(char *));
	if (!array)
		return (0);
	while (i < string)
	{
		while (*s == c && *s != 0)
			s++;
		array[i] = ft_create_string(s, ft_string_len(s, c));
		s = s + ft_string_len(s, c);
		i++;
	}
	array[i] = 0;
	return (array);
}