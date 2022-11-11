/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <diroyer@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 17:36:48 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/11 23:08:16 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

#include <stdlib.h>
#include <struct.h>
#include <string.h>


char	*ft_mega_join(char *s1, char *s2, char *s3);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);

char	**lst_to_tab(t_env *lst);
// ft_atoi.c
int ft_atoi(const char *nptr);

// ft_itoa.c
char *ft_itoa(int nb);

// ft_count_words.c
int	ft_words_count(char const *s, char c);

// ft_strndup.c
char *ft_strndup(const char *s1, int len);

// ft_putendl_fd.c
void ft_putendl_fd(char *s, int fd);

// ft_swap_str.c
void ft_swap_str(char **a, char **b);

// ft_isalpha.c
int ft_isalpha(int c);

// ft_isalnum.c
int ft_isalnum(int c);

// ft_strcmp.c
int ft_strcmp(const char *s1, const char *s2);

// ft_isdigit.c
int ft_isdigit(int c);

// ft_findi.c
int ft_findi(char *str, char find);

// ft_strncmp.c
int ft_strncmp(const char *s1, const char *s2, size_t n);

// ft_strlen.c
size_t ft_strlen(const char *s);

// ft_putstr_fd.c
void ft_putstr_fd(char *s, int fd);

// ft_strchr.c
char *ft_strchr(const char *s, int c);

// ft_putchar_fd.c
void ft_putchar_fd(char c, int fd);

// ft_strjoin.c
char *ft_strjoin(char const *s1, char const *s2);

// ft_split.c
char **ft_split(char const *s, char c);

// ft_strlcat.c
size_t ft_strlcat(char *dst, char const *src, size_t size);

// ft_strdup.c
char *ft_strdup(const char *s1);

// ft_strlcpy.c
size_t ft_strlcpy(char *dst, const char *src, size_t dstsize);

// ft_strcpy.c
void ft_strcpy(char *dst, const char *src);

// ft_strcat.c
void ft_strcat(char *dst, char const *src);

#endif
