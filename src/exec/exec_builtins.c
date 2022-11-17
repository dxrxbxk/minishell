/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 15:49:17 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/17 21:40:45 by momadani         ###   ########.fr       */
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

int	is_builtin(char **av)
{
	int	i;
	t_built *data;

	i = -1;
	data = init_fpointer();
	while (++i < NB_BUILTS)
	{
		if (!ft_strcmp(data[i].cmd, av[0]))
			return (0);
	}
	return (1);
}
/*
int	is_redir(t_redir *redir)
{
	return (redir->type = OUTFILE || redir->type = INFILE ||
			redir->type = APPEND || redir->type = HEREDOC);
}
*/
int	get_exec_builtin(char **av, t_mini *shell)
{
	t_built *data;
	int	ret;
	int	i;

	i = -1;
	ret = 1;
	data = init_fpointer();
	while (++i < NB_BUILTS)
	{
		if (!ft_strcmp(data[i].cmd, av[0]))
			ret = data[i].builtins(shell->env, av, tab_len(av));
	}
	return (ret);
}
/*
int	exec_builtin(char **av, t_mini *shell)
{
	int	ret;
	int	fds[2];

	ret = 1;
	if (is_redir(redir))
	{

	}

}
*/
