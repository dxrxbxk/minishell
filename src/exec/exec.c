/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 17:18:39 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/10 15:20:07 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	init_fpointer(void)
{
	data->builtins[0] = &ft_echo;
	data->builtins[1] = &ft_unset;
	data->builtins[2] = &ft_env;
	data->builtins[3] = &ft_pwd;
	data->builtins[4] = &ft_cd;
	data->builtins[5] = &ft_exit;
}

int	is_builtin(char *str)
{
	if (!ft_strcmp(str, "echo"))
		return (0);
	else if (!ft_strcmp(str, "unset"))
		return (1);
	else if (!ft_strcmp(str, "env"))
		return (2);
	else if (!ft_strcmp(str, "pwd"))
		return (3);
	else if (!ft_strcmp(str, "cd"))
		return (4);
	else if (!ft_strcmp(str, "exit"))
		return (5);
	else if  (!ft_strcmp(str, "export"))
		return (6);
	else
		return (7);
}

int	ft_execve(char *path, char **av, char **env)
{
	check_path();
}
