/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 13:46:34 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/18 22:48:19 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include <sys/types.h>
# include <sys/wait.h>
# include <struct.h>

void	ft_exit_free(t_mini *data, t_child *child, int retval);
int		ft_quit_free_builtin(t_child *child);

int		execution(t_ast *root, t_ast *ast, t_mini *data);

int		launch_child( t_ast *ast, t_mini *data);
int		launch_builtin(t_child *child, t_ast *ast, t_mini *data);

void	exec_child(t_child *child, t_ast *ast, t_mini *data);
void	ft_child_add_back(t_child **child, t_child *elem);
t_child	*ft_child_new(void);

int				ft_check_is_directory(t_mini *data, t_child *child, char *path);
int				ft_get_args(t_child *child, t_ast *ast);

int				ft_get_pipein_redir_rank(t_redir *redir);
int				ft_get_pipeout_redir_rank(t_redir *redir);
int				ft_get_redirections_pipe_seq(t_child *child, t_ast *ast);

void			exec_pipe_child(t_child *child, t_ast *ast, t_mini *data);
int				set_child_status(t_child *child, int exit_status);

void			ft_fill_redir_struct(t_redir *redir, t_redir_type type, char *path, int fd);
t_redir_type	ft_which_redir(t_type type);
int				ft_apply_redirections(t_redir *redir, t_child *child);
int				ft_get_redirections(t_child *child, t_ast *ast);

int		ft_find_cmd_path(t_child *child, t_mini *data);

int		is_directory(char *path);
int		exec_builtin(t_child *child, t_ast *ast, t_mini *shell);
char	*check_path(char **path, char *cmd);
int		is_builtin(t_ast *ast);
int		init_exec(char **av, t_mini *shell);
t_built	*init_fpointer(void);

#endif
