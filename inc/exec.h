/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:46:34 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/17 23:22:07 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <sys/types.h>
# include <sys/wait.h>
# include <struct.h>

void	ft_exit_free(t_mini *data, t_child *child, int retval);

int		execution(t_ast *root, t_ast *ast, t_mini *data);
int		launch_child(t_ast *root, t_ast *ast, t_mini *data);
void	exec_child(t_child *child, t_ast *ast, t_mini *data);
void	ft_child_add_back(t_child **child, t_child *elem);
t_child	*ft_child_new(void);

int		ft_apply_redirections(t_redir *redir, t_child *child, t_mini *data);
int		ft_get_redirections(t_child *child, t_ast *ast, t_mini *data);

int		ft_find_cmd_path(t_child *child, t_mini *data);

int		is_directory(char *path);
int		exec_builtin(char **av, t_mini *shell);
char	*check_path(char **path, char *cmd);
int		is_builtin(char **av);
int		init_exec(char **av, t_mini *shell);
t_built	*init_fpointer(void);

#endif
