/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 19:46:44 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/20 15:34:35 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strlastchr(const char *s, int c)
{
	int	i;
	int j;
	int c_count;

	i = -1;
	c_count = 0;
	j = 0;
	while (s && s[++i])
	{
		if (s[i] == (char)c && c_count == 0)
			c_count = 1;
		else if (s[i] == (char)c && c_count == 1)
		{
			c_count = 0;
			j = i;
		}
	}
	if (s[i] == '\0')
		return ((char *)s + j);
	return (NULL);
}

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	while (i >= 0)
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i--;
	}
	return (NULL);
}
