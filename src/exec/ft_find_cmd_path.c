/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_cmd_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momadani <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 00:01:22 by momadani          #+#    #+#             */
/*   Updated: 2022/11/17 00:20:54 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	ft_strrealloc(char **src, char *cmd, char *prefix)
{
	char	*dest;

	dest = ft_strjoin(prefix, cmd);
	if (*src != cmd)
		free(*src);
	if (!dest)
		ft_error(0, MEMORY);
	*src = dest;
	return (1);
}

static int	ft_try_path(char **env_path, char **pathname, char *cmd)
{
	if (!*env_path)
		return (0);
	ft_strrealloc(pathname, cmd, *env_path);
	if (!access(*pathname, F_OK | X_OK))
		return (1);
	return (ft_try_path((env_path + 1), pathname, cmd));
}

static int	ft_abs_rel_path(t_mini *data, t_child *child)
{
	char	*tmp;

//	if (!access(child->pathname, F_OK | X_OK))
//		return (1);
//	tmp = ft_strjoin("./", child->pathname);
//	free(child->pathname)
//	child->pathname = tmp;
	if (!access(*pathname, F_OK | X_OK))
		return (1);
	ft_error(errno, cmd);
	return (0);
}

int	ft_find_cmd_path(t_child *child, t_mini *data)
{
	char	*cmd;

	cmd = child->argv[0];
	child->pathname = ft_strdup(cmd);
	if (!child->pathname)
		ft_exit_free(data, child,
			ft_error("Memory allocation error\n", NULL, NULL, 1));
	if (ft_strchr(cmd, '/'))
		ft_abs_rel_path(data, child);
	else if (!env->path || !*env->path)
		ft_error(0, PATH);
	else if (!ft_try_path(env->path, pathname, cmd))
		ft_error(errno, cmd);
	return (1);
}
