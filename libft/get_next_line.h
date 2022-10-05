/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 18:49:42 by diroyer           #+#    #+#             */
/*   Updated: 2022/04/08 15:44:57 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <string.h>
// get_next_line_utils.c
char	*ft_substrg(char *s, unsigned int start, size_t len);
char	*ft_strjoing(char *s1, char *s2);
size_t	ft_strleng(char const *str);
char	*ft_strdup(const char *s1);
// get_next_line.c
char	*get_next_line(int fd);

#endif
