/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:28:49 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/18 19:40:36 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H
# define NB_BUILTS 7

#include <struct.h>
// unset.c
int	ft_unset(t_env *lst, char **av, int ac);

// exit.c

// exit.c
int ft_exit(t_env *lst, char **av, int ac);

// cd.c

// cd.c
int ft_cd(t_env *lst, char **av, int ac);

// echo.c

// echo.c
int ft_echo(t_env *lst, char **av, int ac);

// ft_env.c

// ft_env.c
int ft_env(t_env *lst, char **av, int ac);

// export.c

// export.c
int ft_export(t_env *lst, char **av, int ac);

// pwd.c
int ft_pwd(t_env *lst, char **av, int ac);
#endif
