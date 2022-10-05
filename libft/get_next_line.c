/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 18:49:19 by diroyer           #+#    #+#             */
/*   Updated: 2022/04/08 15:50:42 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"
#include <unistd.h>

static char	*ft_strchrg(char *s, char c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			return (s);
		s++;
	}
	if (c == '\0')
		return (s);
	return (NULL);
}

static void	read_line(char **s, int fd)
{
	char	buf[BUFFER_SIZE + 1];
	int		ret;
	char	*tmp;

	ret = read(fd, buf, BUFFER_SIZE);
	while (ret > 0)
	{
		buf[ret] = '\0';
		tmp = *s;
		*s = ft_strjoing(*s, buf);
		free(tmp);
		if (ft_strchrg(buf, '\n'))
			break ;
		ret = read(fd, buf, BUFFER_SIZE);
	}
}

static char	*get_line(char **s)
{
	char		*tmp;
	char		*line;
	int			i;

	i = 0;
	while ((*s)[i] && (*s)[i] != '\n')
		i++;
	if ((*s)[i] == '\n')
		i++;
	line = ft_substrg(*s, 0, i);
	tmp = *s;
	*s = ft_substrg(tmp, i, ft_strleng(tmp) - i);
	free(tmp);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*s = NULL;

	if (fd < 0)
		return (NULL);
	if (!ft_strchrg(s, '\n'))
		read_line(&s, fd);
	if (!s)
		return (NULL);
	if (!s[0])
	{
		free(s);
		s = NULL;
		return (NULL);
	}
	return (get_line(&s));
}
