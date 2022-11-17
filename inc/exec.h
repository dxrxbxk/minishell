/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:46:34 by diroyer           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2022/11/17 00:03:18 by momadani         ###   ########.fr       */
=======
/*   Updated: 2022/11/16 21:47:56 by diroyer          ###   ########.fr       */
>>>>>>> 3b4ea4c8d9860e9f2274f24481fd107805261a56
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
void	ft_child_add_back(t_child **child, t_child *elem);
t_child	*ft_child_new(void);

<<<<<<< HEAD
int		ft_apply_redirections(t_redir *redir, t_child *child, t_mini *data);
int		ft_get_redirections(t_child *child, t_ast *ast, t_mini *data);

=======
int		is_directory(char *path);
>>>>>>> 3b4ea4c8d9860e9f2274f24481fd107805261a56
int		exec_builtin(char **av, t_mini *shell);
char	*check_path(char **path, char *cmd);
int		is_builtin(char **av);
int		init_exec(char **av, t_mini *shell);
t_built	*init_fpointer(void);

#endif
