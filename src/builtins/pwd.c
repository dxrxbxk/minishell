/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:44:24 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/09 19:05:49 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_pwd(t_env *lst, char **av, int ac)
{
	char	*cwd;

	(void)av;
	(void)lst;
	if (ac > 1)
		ft_error("pwd:", "", " too many arguments\n");
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (-1);
	else
		printf("%s\n", cwd);
	free(cwd);
	return (0);
}
