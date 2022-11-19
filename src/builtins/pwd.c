/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:44:24 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/19 21:44:49 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_pwd(t_env *lst, char **av, int ac)
{
	char	*cwd;

	(void)av;
	(void)lst;
	(void)ac;
	if (get_key_value(lst, "PWD"))
		cwd = ft_strdup(get_key_value(lst, "PWD"));
	else
		cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_error("pwd: ", strerror(errno) , NULL, 1));
	else
		printf("%s\n", cwd);
	free(cwd);
	return (0);
}
