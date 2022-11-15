/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:46:34 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/15 18:45:22 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <sys/types.h>
# include <sys/wait.h>
# include <struct.h>

int		execution(t_ast *root, t_ast *ast, t_mini *data);
int		launch_child(t_ast *root, t_ast *ast, t_mini *data);
void	ft_child_add_back(t_child **child, t_child *elem);
t_child	*ft_child_new(void);

char	*check_path(char **path, char *cmd);
int		is_builtin(char **av, t_mini *shell);
int		init_exec(char **av, t_mini *shell);
t_built	*init_fpointer(void);

#endif
