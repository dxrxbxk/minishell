/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diroyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 18:44:24 by diroyer           #+#    #+#             */
/*   Updated: 2022/11/21 01:55:18 by diroyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	ft_pwd(t_env **lst, char **av, int ac)
{
	char	*cwd;
	char	*cpy;
	t_env	*new;

	(void)av;
	(void)ac;
	if (get_key_value(*lst, "PWD"))
		cwd = ft_strdup(get_key_value(*lst, "PWD"));
	else
	{
		cwd = getcwd(NULL, 0);
		cpy = ft_strdup(cwd);
		new = ft_env_new("PWD", cpy);
		ft_env_addback(lst, new);
	}
	if (!cwd)
		return (ft_error("pwd: ", strerror(errno), NULL, 1));
	else
		printf("%s\n", cwd);
	free(cwd);
	return (0);
}
