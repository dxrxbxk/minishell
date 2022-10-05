/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 13:13:52 by diroyer           #+#    #+#             */
/*   Updated: 2022/04/08 15:46:26 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"

size_t	ft_strleng(char const *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

static void	ft_strcatg(char *dst, char const *src)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i])
		i++;
	while (src[j])
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = 0;
}

static void	ft_strcpyg(char *dst, const char *src)
{
	size_t	i;

	if (!src)
		return ;
	i = 0;
	while (src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
}

char	*ft_strjoing(char *s1, char *s2)
{
	size_t	len;
	char	*array;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		len = ft_strleng(s2);
	else
		len = ft_strleng(s1) + ft_strleng(s2);
	array = malloc(sizeof(char) * (len + 1));
	if (!array)
		return (NULL);
	array[0] = '\0';
	ft_strcpyg(array, s1);
	ft_strcatg(array, s2);
	return (array);
}

char	*ft_substrg(char *s, unsigned int start, size_t len)
{
	char	*array;
	size_t	slen;
	size_t	i;

	if (!s)
		return (NULL);
	slen = ft_strleng(s);
	if (start >= slen)
		len = 0;
	else if (start + len > slen)
		len = slen - start;
	array = malloc(len + 1);
	if (!array)
		return (NULL);
	i = 0;
	while (i < len)
	{
		array[i] = s[start + i];
		i++;
	}
	array[i] = '\0';
	return (array);
}
