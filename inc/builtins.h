/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:28:49 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/09 14:43:51 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

#include <struct.h>

// unset.c
void unset(t_env *lst, char *str);

// exit.c
int ft_exit(char **av, int ac);

// cd.c
int ft_cd(t_env *lst, char **av, int ac);

// env.c
void ft_env(t_env *lst);

// echo.c
int ft_echo(char **av, int ac);

// export.c
int ft_export(t_env *lst, t_env *cpy, char **av, int ac);

// pwd.c
int ft_pwd(void);

#endif
