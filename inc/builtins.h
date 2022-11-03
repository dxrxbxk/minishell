/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:28:49 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/03 16:55:49 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include <struct.h>

// unset.c
void unset(t_env *lst, char *str);

// exit.c
int ft_isnum(char *str);
long result_check(long result, int sign, int over, char *nptr);
long ft_atoi2(const char *nptr);
int ft_exit(char **av, int ac);

// cd.c
void replace_pwd(char *replace, t_env *lst);
int ft_cd(t_env *lst, char **av, int ac);

// env.c
void ft_env(t_env *lst);

// echo.c
int ft_cmpchar(char *str, char c);
int ft_echo_print(char **av, int ac, int i, int n);
int ft_echo(char **av, int ac);

// export.c
int export_key(char *str);
t_env *lst_copy(t_env *lst);
void sort_list(t_env *tosort);
int ft_export(t_env *lst, char **av, int ac);

// pwd.c
int ft_pwd(void);

#endif
