/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <momadani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 15:49:17 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/20 05:24:28 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <minishell.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sysmacros.h>

int	is_directory(char *path)
{
	struct stat sb;

	if (lstat(path, &sb) == -1)
		perror("lstat");
	if (sb.st_mode & S_IFDIR)
		ft_error(path, ": Is a directory\n", NULL, 1);
	return (0);
}

t_built	*init_fpointer(void)
{
	static t_built	data[NB_BUILTS];
	
	data[0].builtins = &ft_echo;
	data[0].cmd = "echo";
	data[1].builtins = &ft_unset;
	data[1].cmd = "unset";
	data[2].builtins = &ft_env;
	data[2].cmd = "env";
	data[3].builtins = &ft_pwd;
	data[3].cmd = "pwd";
	data[4].builtins = &ft_cd;
	data[4].cmd = "cd";
	data[5].builtins = &ft_exit;
	data[5].cmd = "exit";
	data[6].builtins = &ft_export;
	data[6].cmd = "export";
	return (data);
}

int	is_builtin(t_ast *ast)
{
	t_built *data;
	char	*cmd;
	int		i;

	cmd = NULL;
	while (ast && !ast->token->str)
		ast = ast->right;
	if (ast)
		cmd = ast->token->str;
	if (!ast || !cmd)
		return (0);
	data = init_fpointer();
	i = -1;
	while (++i < NB_BUILTS)
	{
		if (!ft_strcmp(data[i].cmd, cmd))
			return (1);
	}
	return (0);
}

int	ft_quit_free_builtin(t_child *child)
{
	//free current child;
	g_status = child->status;
	return (0);
}

int	exec_builtin(t_child *child, t_ast *ast, t_mini *shell)
{
	t_built	*data;
	int		ret;
	int		i;

	if (ft_get_args(child, ast->right) != 0)
		return (ft_quit_free_builtin(child));
	i = -1;
	ret = 1;
	data = init_fpointer();
	while (++i < NB_BUILTS)
	{
		if (!ft_strcmp(data[i].cmd, child->argv[0]))
			ret = data[i].builtins(shell->env, child->argv, tab_len(child->argv));
	}
	return (ret);
}

int	ft_save_main_fds(int fds[2], t_child *child)
{
	if (!child->redir)
		return (0);
	fds[0] = dup(0);
	if (fds[0] == -1)
		return (set_child_status(child, ft_error("dup: ", strerror(errno), NULL, 1)));
	fds[1] = dup(1);
	if (fds[1] == -1)
		return (set_child_status(child, ft_error("dup: ", strerror(errno), NULL, 1)));	
	return (0);
}

int	ft_restore_main_fds(int fds[2], t_child *child)
{
	if (!child->redir)
		return (0);
	if (dup2(fds[0], 0) == -1)
		return (set_child_status(child, ft_error("dup2: ", strerror(errno), NULL, 1)));
	if (close(fds[0]) == -1)
		return (set_child_status(child, ft_error("close: ", strerror(errno), NULL, 1)));
	if (dup2(fds[1], 1) == -1)
		return (set_child_status(child, ft_error("dup2: ", strerror(errno), NULL, 1)));
	if (close(fds[1]) == -1)
		return (set_child_status(child, ft_error("close: ", strerror(errno), NULL, 1)));
	return (0);
}

int	launch_builtin(t_child *child, t_ast *ast, t_mini *data)
{
	int	main_fds[2];

	if (ft_get_cmd_redirections(child, ast->left) != 0)
		return (ft_quit_free_builtin(child));
	if (ft_save_main_fds(main_fds, child) != 0)
		return (ft_quit_free_builtin(child));
	if (ft_apply_redirections(child->redir, child) != 0)
		return (ft_quit_free_builtin(child));
	g_status = exec_builtin(child, ast, data);
	if (ft_restore_main_fds(main_fds, child) != 0)
		return (ft_quit_free_builtin(child));
//	release only current child
	return (0);
}
