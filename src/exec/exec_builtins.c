/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 15:49:17 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/12 15:54:06 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static int	tab_len(char **av)
{
	int i;

	i = 0;
	while (av[i])
		i++;
	return (i);
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

int	is_builtin(char **av, t_mini *shell)
{
	int	i;
	t_built *data;

	i = -1;
	data = init_fpointer();
	while (++i < NB_BUILTS)
	{
		if (!ft_strcmp(data[i].cmd, av[0]))
			return (data[i].builtins(shell->env, av, tab_len(av)));
	}
	return (1);
}