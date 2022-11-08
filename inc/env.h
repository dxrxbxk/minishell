/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:30:29 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/08 19:37:21 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

#include <struct.h>

// env.c
int	get_shlvl(t_mini *data);
char	**create_env(void);
int free_data(t_mini *data);
int get_env(t_mini *data, char **env);
int get_path(t_mini *data, char **env);

// env_utils.c
void ft_env_addback(t_env **first, t_env *new);
t_env *ft_env_new(void *key, void *value);
void print_env(t_env *print);
char *get_env_str(t_env *lst, char *get);
void ft_replace_env(t_env *lst, char *cmp, char *value);

#endif
