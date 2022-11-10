/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 16:30:29 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/10 16:22:21 by diroyer          ###   ########.fr       */
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
void	print_env(t_env *print);
char *get_env_str(t_env *lst, char *get);
void ft_replace_env(t_env *lst, char *cmp, char *value);
void	ft_join_env(t_env *lst, char *cmp, char *value);
void	print_env_export(t_env *print);
// env_utils_2.c
t_env	*lst_copy(t_env *lst);
void	sort_list(t_env *lst);




int	ft_count_words2(char const *s, char c); // delete this

#endif
