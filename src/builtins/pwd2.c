/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:44:24 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/19 19:25:35 by momadani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_pwd(t_env *lst, char **av, int ac)
{
	char	*cwd;

	(void)av;
	(void)lst;
	(void)ac;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1); //add error msg
//		return (ft_error("pwd: cwd: ", strerror(errno), NULL, 1)); add msg like bash
	else
		printf("%s\n", cwd);
	free(cwd);
	return (0);
}
