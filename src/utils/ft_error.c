/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:33:59 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/04 17:42:34 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <utils.h>
#include <string.h>
#include <stdlib.h>

static char	*ft_strjoin_error(char *s1, char *s2, char *s3)
{
	size_t	len;
	char	*array;

	if (!s1 && !s2 && !s3)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2); + ft_strlen(s3);
	array = malloc(sizeof(char) * (len + 1));
	if (!array)
		return (NULL);
	array[0] = '\0';
	ft_strcpy(array, s1);
	ft_strcat(array, s2);
	ft_strcat(array, s3);
	return (array);
}

void	ft_error(char *msg, char *var, char *msg2)
{
	char *print;

	print = ft_strjoin_error(msg, var, msg2);
	if (!print)
		return ;
	ft_putstr_fd(print, 2);
	free(print);
}
